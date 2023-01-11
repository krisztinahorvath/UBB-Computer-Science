package Model.statements;

import Model.adt.MyIDict;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.IType;
import Model.types.StringType;
import Model.values.IValue;
import Model.values.StringValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFile implements IStatement{
    private final IExpression expr;

    public CloseReadFile(IExpression e){
        expr = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        IValue value = expr.eval(state.getSymTable(), state.getHeap());
        if (!value.getType().equals(new StringType()))
            throw new StmtExeException(String.format("ERROR: %s does not evaluate to StringValue", expr));
        StringValue fileName = (StringValue) value;
        MyIDict<String, BufferedReader> fileTable = state.getFileTable();
        if (!fileTable.contains(fileName.getValue()))
            throw new StmtExeException(String.format("ERROR: %s is not present in the FileTable", value));
        BufferedReader br = fileTable.lookUp(fileName.getValue());
        try {
            br.close();
        } catch (IOException e) {
            throw new StmtExeException(String.format("ERROR: Unexpected error in closing %s", value));
        }
        fileTable.remove(fileName.getValue());
        state.setFileTable(fileTable);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CloseReadFile(expr.deepCopy());
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException {
        if (expr.typeCheck(typeEnv).equals(new StringType()))
            return typeEnv;
        else
            throw new StmtExeException("ERROR: CloseReadFile requires a string expression.");
    }

    @Override
    public String toString() {
        return String.format("CloseReadFile(%s)", expr.toString());
    }
}
