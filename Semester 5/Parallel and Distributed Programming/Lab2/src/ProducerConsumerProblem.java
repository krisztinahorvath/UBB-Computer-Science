import java.util.Calendar;
import java.util.LinkedList;
import java.util.Queue;
import java.util.TimeZone;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumerProblem {
    private static final int VECTOR_SIZE = 5;
    private final int[] vector1 = {1, 2, 3, 4, 5};
    private final int[] vector2 = {6, 7, 8, 9, 10};
    private static final Queue<Integer> productsQueue = new LinkedList<>();
    private static final Lock mutex = new ReentrantLock();
    private static final Condition condition = mutex.newCondition();
    static int result = 0;
    boolean producerDone = false;

    private void produce(){
        for(int i = 0; i < VECTOR_SIZE; i++) {
            int product = vector1[i] * vector2[i];
            mutex.lock();

            productsQueue.add(product); // put product into the queue
            System.out.println("Producer product: " + product +  " timestamp: " + System.nanoTime());
            condition.signal(); // notify the consumer

            mutex.unlock();
        }

        producerDone = true;
    }

    private void consume() {
        while (true) {
            mutex.lock();
            try {
                while (productsQueue.isEmpty() && !producerDone) {
                    condition.await(); // wait for the producer to compute a product
                }

                if (productsQueue.isEmpty()) {
                    break; // the producer is done and all products were summed up from the queue
                }

                int product = productsQueue.remove();
                result += product;
                System.out.println("Consumer sum: " + result + " timestamp: " + System.nanoTime());
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            } finally {
                mutex.unlock();
            }
        }
    }


    public static void main(String[] args) throws InterruptedException {
        ProducerConsumerProblem producerConsumerProblem = new ProducerConsumerProblem();

        Thread producerThread = new Thread(producerConsumerProblem::produce);
        Thread consumerThread = new Thread(producerConsumerProblem::consume);

        producerThread.start();
        consumerThread.start();

        producerThread.join(); // make sure it finished producing before the consumer finishes
        consumerThread.join();

        System.out.println("\nThe scalar product is: " + result);
    }
}