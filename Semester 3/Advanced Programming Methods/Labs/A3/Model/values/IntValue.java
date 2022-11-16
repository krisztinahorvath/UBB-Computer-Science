package Model.values;

import Model.types.IType;
import Model.types.IntType;

public class IntValue implements IValue {
    private final int value;

    public IntValue(int v){
        this.value = v;
    }

    public int getValue(){
        return value;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public IValue deepCopy() {
        return new IntValue(value);
    }

    @Override
    public boolean equals(Object anotherValue){
        if(!(anotherValue instanceof IntValue))
            return false;
        IntValue castVal = (IntValue) anotherValue;
        return value == castVal.value;
    }
    @Override
    public String toString() {
        return String.format("%d", value);
    }
}
