package Model.statements;

import Model.adt.MyDict;
import Model.adt.MyIDict;
import Model.adt.MyIStack;
import Model.adt.MyStack;
import Model.programState.ProgramState;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.util.Map;

public class ForkStatement implements IStatement{
    private final IStatement statement;

    public ForkStatement(IStatement statement){
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        MyIStack<IStatement> newStack = new MyStack<>();
        newStack.push(statement);

        MyIDict<String, IValue> newSymTable = new MyDict<>();
        for (Map.Entry<String, IValue> e: state.getSymTable().getContent().entrySet()){
            newSymTable.put(e.getKey(), e.getValue().deepCopy());
        }

        return new ProgramState(newStack, newSymTable, state.getOut(), state.getFileTable(), state.getHeap());
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(statement.deepCopy());
    }

    @Override
    public String toString(){
        return String.format("Fork(%s)", statement.toString());
    }
}
