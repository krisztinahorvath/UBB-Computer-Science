package Model.expressions;

import Model.adt.MyIDict;
import Model.types.BoolType;
import Model.values.BoolValue;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;

import java.util.Objects;

public class LogicExpression implements IExpression{
    IExpression expr1;
    IExpression expr2;
    String operator;

    public LogicExpression(IExpression e1, IExpression e2, String o){
        expr1 = e1;
        expr2 = e2;
        operator = o;
    }
    @Override
    public IValue eval(MyIDict<String, IValue> symTable) throws ExprEvalException, ADTException, DivisionByZero {
        IValue value1, value2;
        value1 = expr1.eval(symTable);
        if (value1.getType().equals(new BoolType())) {
            value2 = expr2.eval(symTable);
            if (value2.getType().equals(new BoolType())) {
                BoolValue bool1 = (BoolValue) value1;
                BoolValue bool2 = (BoolValue) value2;
                boolean b1, b2;
                b1 = bool1.getValue();
                b2 = bool2.getValue();
                if (Objects.equals(operator, "and")) {
                    return new BoolValue(b1 && b2);
                } else if (Objects.equals(operator, "or")) {
                    return new BoolValue(b1 || b2);
                }
            } else {
                throw new ExprEvalException("Second operand is not a boolean.");
            }
        } else {
            throw new ExprEvalException("First operand is not a boolean.");
        }
        return null;
    }

    @Override
    public IExpression deepCopy() {
        return new LogicExpression(expr1.deepCopy(), expr2.deepCopy(), operator);
    }

    @Override
    public String toString() {
        return expr1.toString() + " " + operator + " " + expr2.toString();
    }
}
