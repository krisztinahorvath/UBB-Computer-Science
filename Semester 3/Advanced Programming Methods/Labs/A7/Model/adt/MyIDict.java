package Model.adt;

import exceptions.ADTException;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public interface MyIDict<T1,T2> {
    void put(T1 key, T2 value);
    void update(T1 key, T2 value) throws ADTException;
    void remove(T1 key) throws ADTException;
    boolean contains(T1 key);
    T2 lookUp(T1 key) throws ADTException;
    Collection<T2> values();
    Set<T1> keySet();
    Map<T1, T2> getContent();

    MyIDict<T1,T2> deepCopy() throws ADTException;
}
