package Model.statements;

import Model.adt.MyDict;
import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.IType;
import Model.types.RefType;
import Model.values.IValue;
import Model.values.RefValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.sql.Ref;

public class NewStatement implements IStatement{
    private String variableName;
    private IExpression expression;

    public NewStatement(String variableName, IExpression expression){
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        MyIDict<String, IValue> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();

        if(!symTable.contains(variableName))
            throw new StmtExeException(String.format("%s is not in the Symbol Table", variableName));

        IValue variableValue = symTable.lookUp(variableName);
        if(!(variableValue.getType() instanceof RefType))
            throw new StmtExeException(String.format("%s is not a RefType", variableName));

        IValue evaluated = expression.eval(symTable, heap);
        IType locationType = ((RefValue)variableValue).getLocationType();
        if (!locationType.equals(evaluated.getType()))
            throw new StmtExeException(String.format("%s not of %s", variableName, evaluated.getType()));

        int newPosition = heap.add(evaluated);
        symTable.put(variableName, new RefValue(newPosition, locationType));
        state.setSymTable(symTable);
        state.setHeap(heap);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new NewStatement(variableName, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("New(%s, %s)", variableName, expression);
    }
}
