import Message.Message;
import Message.CloseMessage;
import Message.SubscribeMessage;
import Message.UpdateMessage;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import mpi.MPI;

public class DSM {
    private Map<String, Set<Integer>> subscribers;
    private Map<String, Integer> variables;
    private static final Lock mutex = new ReentrantLock();

    public DSM() {
        this.variables = new HashMap<>();
        this.variables.put("a", 1);
        this.variables.put("b", 2);
        this.variables.put("c", 3);

        this.subscribers = new HashMap<>();
        this.subscribers.put("a", new HashSet<>());
        this.subscribers.put("b", new HashSet<>());
        this.subscribers.put("c", new HashSet<>());
    }

    public void setVariable(String variable, int value) {
        mutex.lock();
        variables.put(variable, value);
        mutex.unlock();
    }

    public void updateVariable(String variable, int value) {
        setVariable(variable, value);
        sendMessageToSubscribers(variable, new UpdateMessage(variable, value));
    }

    public void subscribeToVariable(String variable) {
        Set<Integer> subscribersToVariable = subscribers.get(variable);
        subscribersToVariable.add(MPI.COMM_WORLD.Rank());

        subscribers.put(variable, subscribersToVariable);
        sendMessageToAll(new SubscribeMessage(variable, MPI.COMM_WORLD.Rank()));
    }

    public void compareAndExchange(String variable, int oldValue, int newValue) {
        mutex.lock();

        try{
            // only nodes that are subscribed to a variable are allowed to change it
            if (subscribers.get(variable).contains(MPI.COMM_WORLD.Rank()) && variables.get(variable).equals(oldValue))
                updateVariable(variable, newValue);
        } finally {
            mutex.unlock();
        }
    }

    public void syncSubscription(String variable, int rank) {
        Set<Integer> subscribersToVariable = subscribers.get(variable);
        subscribersToVariable.add(rank);
        subscribers.put(variable, subscribersToVariable);
    }

    public void sendMessageToSubscribers(String variable, Message message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() == i || !subscribers.get(variable).contains(i))
                continue;

            MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
        }
    }

    public void sendMessageToAll(Message message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() == i && !(message instanceof CloseMessage))
                continue;

            MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
        }
    }

    public void close() {
        sendMessageToAll(new CloseMessage());
    }

    @Override
    public String toString() {
        return "subscribers = " + subscribers + "\n\t\t\t" + "variables = " + variables + "\n";
    }
}