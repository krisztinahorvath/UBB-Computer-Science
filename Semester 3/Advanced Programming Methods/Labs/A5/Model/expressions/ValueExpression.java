package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.statements.VariableDeclarationStatement;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.ExprEvalException;

public class ValueExpression implements IExpression{
    IValue value;

    public ValueExpression(IValue v){
        value = v;
    }
    @Override
    public IValue eval(MyIDict<String, IValue> symTable, MyIHeap heap) throws ExprEvalException, ADTException {
        return value;
    }

    @Override
    public IExpression deepCopy() {
        return new ValueExpression(value);
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
