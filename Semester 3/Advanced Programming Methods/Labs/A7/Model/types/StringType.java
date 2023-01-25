package Model.types;

import Model.values.IValue;
import Model.values.StringValue;

public class StringType implements IType{
    @Override
    public boolean equals(IType anotherType) {
        return anotherType instanceof StringType;
    }

    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }

    @Override
    public IType deepCopy() {
        return new StringType();
    }

    @Override
    public String toString(){
        return "string";
    }
}
