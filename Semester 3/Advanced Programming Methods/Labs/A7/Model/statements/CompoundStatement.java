package Model.statements;

import Model.adt.MyIDict;
import Model.adt.MyIStack;
import Model.programState.ProgramState;
import Model.types.IType;
import exceptions.ADTException;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class CompoundStatement implements  IStatement{
    IStatement firstStmt;
    IStatement secondStmt;

    public CompoundStatement(IStatement f, IStatement s){
        firstStmt = f;
        secondStmt = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException {
        MyIStack<IStatement> stack = state.getExeStack();
        stack.push(secondStmt);
        stack.push(firstStmt);
        state.setExeStack(stack);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CompoundStatement(firstStmt.deepCopy(), secondStmt.deepCopy());
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException {
        return secondStmt.typeCheck(firstStmt.typeCheck(typeEnv));
    }

    @Override
    public String toString() {
        return String.format("(%s|%s)", firstStmt.toString(), secondStmt.toString());
    }
}
