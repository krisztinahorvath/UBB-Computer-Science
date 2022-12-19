package Model.adt;

import Model.values.IValue;
import exceptions.ADTException;

import java.util.HashMap;

public class MyHeap implements MyIHeap{
    private HashMap<Integer, IValue> heap;
    private Integer freeLocationValue;

    public Integer newValue(){
        freeLocationValue += 1;
        while (freeLocationValue == 0 || heap.containsKey(freeLocationValue))
            freeLocationValue += 1;
        return freeLocationValue;
    }

    public MyHeap(){
        heap = new HashMap<>();
        freeLocationValue = 1;
    }

    @Override
    public Integer getFreeValue() {
        return freeLocationValue;
    }

    @Override
    public HashMap<Integer, IValue> getContent() {
        return heap;
    }

    @Override
    public void setContent(HashMap<Integer, IValue> newMap) {
        heap = newMap;
    }


    @Override
    public Integer add(IValue value) {
        heap.put(freeLocationValue, value);
        Integer toReturn = freeLocationValue;
        freeLocationValue = newValue();
        return toReturn;
    }

    @Override
    public void update(Integer position, IValue value) throws ADTException {
        if (!heap.containsKey(position))
            throw new ADTException(String.format("ERROR: %d is not present in the heap!", position));
        heap.put(position, value);
    }

    @Override
    public IValue get(Integer position) throws ADTException {
        if (!heap.containsKey(position))
            throw new ADTException(String.format("ERROR: %d is not present in the heap", position));
        return heap.get(position);
    }
}
