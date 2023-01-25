package Model.adt;

import exceptions.ADTException;

import java.util.Deque;

public interface MyIStack<T> extends Iterable<T>{
    T pop() throws ADTException;
    void push(T v);
    T peek() throws ADTException;
    boolean isEmpty();
    Deque<T> getStack();
}
