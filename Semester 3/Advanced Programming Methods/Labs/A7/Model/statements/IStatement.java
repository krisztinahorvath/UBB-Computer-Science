package Model.statements;

import Model.adt.MyIDict;
import Model.programState.ProgramState;
import Model.types.IType;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero;

    IStatement deepCopy();

    MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException;

}

