package Model.expressions;

import Model.adt.MyIDict;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;

public interface IExpression {
    IValue eval(MyIDict<String, IValue> symTable) throws ExprEvalException, ADTException, DivisionByZero;
    IExpression deepCopy();
}
