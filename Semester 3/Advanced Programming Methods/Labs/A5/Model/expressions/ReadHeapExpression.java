package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
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
    public String toString(){
        return String.format("ReadHeap(%s)", expression);
    }
}
