package Model.statements;

import Model.adt.MyIDict;
import Model.adt.MyIHeap;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.values.IValue;
import Model.values.RefValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.sql.Ref;

public class WriteHeapStatement implements IStatement{
    private final String variableName;
    private final IExpression expression;

    public WriteHeapStatement(String variableName, IExpression expression){
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        MyIDict<String, IValue> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();

        if(!symTable.contains(variableName))
            throw new StmtExeException(String.format("%s not present in the Symbol table", variableName));

        IValue value = symTable.lookUp(variableName);
        if(!(value instanceof RefValue))
            throw new StmtExeException(String.format("%s not of RefType", value));

        RefValue refValue = (RefValue) value;
        IValue evaluated = expression.eval(symTable, heap);
        if(!evaluated.getType().equals(refValue.getLocationType()))
            throw new StmtExeException(String.format("%s not of %s", evaluated, refValue.getLocationType()));

        heap.update(refValue.getAddress(), evaluated);
        state.setHeap(heap);

        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new WriteHeapStatement(variableName, expression.deepCopy());
    }

    @Override
    public String toString(){
        return String.format("WriteHeap(%s, %s)", variableName, expression);
    }
}
