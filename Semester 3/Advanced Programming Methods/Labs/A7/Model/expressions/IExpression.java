package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.types.IType;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;

public interface IExpression {
    IValue eval(MyIDict<String, IValue> symTable, MyIHeap heap) throws ExprEvalException, ADTException, DivisionByZero;
    IExpression deepCopy();
    IType  typeCheck(MyIDict<String, IType> typeEnv) throws ExprEvalException, ADTException;
}
