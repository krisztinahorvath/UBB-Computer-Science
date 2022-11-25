package Model.types;
import Model.values.IValue;

public interface IType {
    boolean equals(IType anotherType);
    IValue defaultValue();

    IType deepCopy();
}
