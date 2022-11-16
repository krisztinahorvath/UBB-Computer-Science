package Model.values;

import Model.types.IType;
import Model.types.BoolType;

public class BoolValue implements IValue {
    private final boolean value;

    public BoolValue(boolean v){
        value = v;
    }

    public boolean getValue(){
        return value;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(value);
    }

    @Override
    public boolean equals(Object anotherValue){
        if(!(anotherValue instanceof BoolValue))
            return false;
        BoolValue castVal = (BoolValue) anotherValue;
        return this.value == castVal.value;
    }

    public String toString(){
        return value ? "true" : "false";
    }
}
