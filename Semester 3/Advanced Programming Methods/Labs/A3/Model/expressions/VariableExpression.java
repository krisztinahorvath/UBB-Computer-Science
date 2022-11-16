package Model.expressions;

import Model.adt.MyIDict;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.ExprEvalException;

public class VariableExpression implements IExpression{
    String key;

    public VariableExpression(String k){
        key = k;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> symTable) throws ExprEvalException, ADTException {
        return symTable.lookUp(key);
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(key);
    }

    @Override
    public String toString(){
        return key;
    }
}
