package Model.statements;

import Model.programState.ProgramState;
import exceptions.ADTException;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class NopStatement implements IStatement{
    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException {
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new NopStatement();
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
