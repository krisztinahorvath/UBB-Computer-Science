package Model.expressions;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.types.IntType;
import Model.values.BoolValue;
import Model.values.IValue;
import Model.values.IntValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;

import java.util.Objects;

public class RelationalExpression implements IExpression{
    IExpression expr1;
    IExpression expr2;
    String operator;

    public RelationalExpression(String op, IExpression e1, IExpression e2){
        expr1 = e1;
        expr2 = e2;
        operator = op;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> symTable, MyIHeap heap) throws ExprEvalException, ADTException, DivisionByZero {
        IValue value1, value2;
        value1 = expr1.eval(symTable, heap);
        if (value1.getType().equals(new IntType())) {
            value2 = expr2.eval(symTable, heap);
            if (value2.getType().equals(new IntType())) {
                IntValue val1 = (IntValue) value1;
                IntValue val2 = (IntValue) value2;
                int v1, v2;
                v1 = val1.getValue();
                v2 = val2.getValue();
                if (Objects.equals(this.operator, "<"))
                    return new BoolValue(v1 < v2);
                else if (Objects.equals(this.operator, "<="))
                    return new BoolValue(v1 <= v2);
                else if (Objects.equals(this.operator, "=="))
                    return new BoolValue(v1 == v2);
                else if (Objects.equals(this.operator, "!="))
                    return new BoolValue(v1 != v2);
                else if (Objects.equals(this.operator, ">"))
                    return new BoolValue(v1 > v2);
                else if (Objects.equals(this.operator, ">="))
                    return new BoolValue(v1 >= v2);
            } else
                throw new ExprEvalException("ERROR: Second operand not integer.");
        } else
            throw new ExprEvalException("ERROR: First operand not integer.");
        return null;
    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(operator, expr1.deepCopy(), expr2.deepCopy());
    }

    @Override
    public String toString() {
        return expr1.toString() + " " + operator + " " + expr2.toString();
    }
}
