package Model.statements;

import Model.adt.MyIDict;
import Model.programState.ProgramState;
import Model.types.IType;
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
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
