package Model.values;

import Model.types.IType;
import Model.types.StringType;

public class StringValue implements IValue{
    private final String value;

    public StringValue(String v){
        value = v;
    }
    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(value);
    }

    @Override
    public boolean equals(Object anotherValue) {
        if (!(anotherValue instanceof StringValue))
            return false;
        StringValue castValue = (StringValue) anotherValue;
        return this.value.equals(castValue.value);
    }

    public String getValue() {
        return this.value;
    }

    @Override
    public String toString() {
        return "\"" + this.value + "\"";
    }
}
