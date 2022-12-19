package Model.statements;

import Model.adt.MyIDict;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.IType;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class AssignStatement implements IStatement{
    private final String key;
    private final IExpression expression;

    public AssignStatement(String k, IExpression e){
        key = k;
        expression = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        MyIDict<String, IValue> symbolTable = state.getSymTable();

        if (symbolTable.contains(key)) {
            IValue value = expression.eval(symbolTable, state.getHeap());
            IType typeId = (symbolTable.lookUp(key)).getType();
            if (value.getType().equals(typeId)) {
                symbolTable.update(key, value);
            } else {
                throw new StmtExeException("ERROR: Assigment mismatch:  " + key);
            }
        } else {
            throw new StmtExeException("ERROR: Undeclared variable:  " + key);
        }
        state.setSymTable(symbolTable);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(key, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("%s = %s", key, expression.toString());
    }
}
