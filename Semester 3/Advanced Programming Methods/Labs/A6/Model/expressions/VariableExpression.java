package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.types.IType;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.ExprEvalException;

public class VariableExpression implements IExpression{
    String key;

    public VariableExpression(String k){
        key = k;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> symTable, MyIHeap heap) throws ExprEvalException, ADTException {
        return symTable.lookUp(key);
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(key);
    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws ExprEvalException, ADTException {
        return typeEnv.lookUp(key);
    }

    @Override
    public String toString(){
        return key;
    }
}
