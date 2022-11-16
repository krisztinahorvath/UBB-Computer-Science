package Model.statements;

import Model.programState.ProgramState;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero;

    IStatement deepCopy();

}

