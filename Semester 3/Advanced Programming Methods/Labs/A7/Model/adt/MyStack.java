package Model.adt;

import Model.statements.IStatement;
import exceptions.ADTException;

import java.util.Deque;
import java.util.Iterator;
import java.util.LinkedList;

public class MyStack<T> implements MyIStack<T> {
    private final Deque<T> deque;

    public MyStack(){
        deque = new LinkedList<>();
    }

    @Override
    public T pop() throws ADTException {
        if(deque.isEmpty())
            throw new ADTException("ERROR: EMPTY STACK!");
        return deque.pop();
    }

    @Override
    public void push(T v) {
        deque.push(v);
    }

    @Override
    public T peek() throws ADTException {
        if(deque.isEmpty())
            throw new ADTException("ERROR: EMPTY STACK!");
        return deque.peek();
    }

    @Override
    public boolean isEmpty() {
        return deque.isEmpty();
    }

    @Override
    public Deque<T> getStack() {
        return deque;
    }

    @Override
    public Iterator<T> iterator() {
        return deque.iterator();
    }
}
