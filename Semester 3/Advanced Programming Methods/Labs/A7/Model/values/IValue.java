package Model.values;

import Model.types.IType;

public interface IValue {
    IType getType();
    IValue deepCopy();
}
