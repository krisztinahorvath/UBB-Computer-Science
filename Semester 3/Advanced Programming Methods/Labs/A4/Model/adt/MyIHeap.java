package Model.adt;

import Model.values.IValue;
import exceptions.ADTException;

import java.util.HashMap;
import java.util.Map;

public interface MyIHeap {
    Integer getFreeValue();
    Map<Integer, IValue> getContent();
    void setContent(HashMap<Integer, IValue> newMap);
    Integer add(IValue value);
    void update(Integer position, IValue value) throws ADTException;
    IValue get(Integer position) throws ADTException;
}
