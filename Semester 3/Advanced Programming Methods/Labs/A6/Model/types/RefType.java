package Model.types;

import Model.values.IValue;
import Model.values.RefValue;

import java.sql.Ref;

public class RefType implements IType {
    private IType inner;

    public RefType(IType inner){
        this.inner = inner;
    }

    public IType getInner() { return inner; }

    @Override
    public boolean equals(IType anotherType) {
        if (anotherType instanceof RefType)
            return inner.equals(((RefType) anotherType).getInner());
        return false;
    }

    @Override
    public IValue defaultValue() {
        return new RefValue(0, inner);
    }

    @Override
    public IType deepCopy() {
        return new RefType(inner.deepCopy());
    }

    @Override
    public String toString(){
        return String.format("Ref(%s)", inner);
    }
}
