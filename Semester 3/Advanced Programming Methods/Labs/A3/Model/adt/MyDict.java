package Model.adt;

import exceptions.ADTException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class MyDict<T1, T2> implements MyIDict<T1, T2> {
    HashMap<T1, T2> dict;

    public MyDict(){
        dict = new HashMap<>();
    }

    @Override
    public void put(T1 key, T2 value) {
        dict.put(key, value);
    }

    @Override
    public void update(T1 key, T2 value) throws ADTException {
        if (!contains(key))
            throw new ADTException("ERROR: UNDEFINED KEY " + key);
        dict.put(key, value);
    }

    @Override
    public void remove(T1 key) throws ADTException {
        if (!contains(key))
            throw new ADTException("ERROR: UNDEFINED KEY " + key);
        dict.remove(key);
    }

    @Override
    public boolean contains(T1 key) {
        return dict.containsKey(key);
    }

    @Override
    public T2 lookUp(T1 key) throws ADTException {
        if (!contains(key))
            throw new ADTException("ERROR: UNDEFINED KEY " + key);
        return dict.get(key);
    }

    @Override
    public Collection<T2> values() {
        return dict.values();
    }

    @Override
    public Set<T1> keySet() {
        return dict.keySet();
    }
}