package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.types.IType;
import Model.types.RefType;
import Model.values.IValue;
import Model.values.RefValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;

public class ReadHeapExpression implements IExpression{
    private IExpression expression;

    public ReadHeapExpression(IExpression expression){
        this.expression = expression;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> symTable, MyIHeap heap) throws ExprEvalException, ADTException, DivisionByZero {
        IValue val = expression.eval(symTable, heap);
        if(!(val instanceof RefValue))
            throw new ExprEvalException(String.format("%s is not of RefType",val));

        RefValue refValue = (RefValue) val;
        return heap.get(refValue.getAddress());
    }

    @Override
    public IExpression deepCopy() {
        return new ReadHeapExpression(expression.deepCopy());
    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws ExprEvalException, ADTException {
        IType type = expression.typeCheck(typeEnv);
        if (type instanceof RefType) {
            RefType refType = (RefType) type;
            return refType.getInner();
        } else
            throw new ExprEvalException("ERROR: The rH argument is not a RefType.");
    }

    @Override
    public String toString(){
        return String.format("ReadHeap(%s)", expression);
    }
}
