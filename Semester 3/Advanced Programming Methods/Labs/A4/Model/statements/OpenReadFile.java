package Model.statements;

import Model.adt.MyIDict;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.StringType;
import Model.values.IValue;
import Model.values.StringValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenReadFile implements IStatement{
    private final IExpression expr;

    public OpenReadFile(IExpression e){
        expr = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        IValue value = expr.eval(state.getSymTable(), state.getHeap());
        if (value.getType().equals(new StringType())) {
            StringValue fileName = (StringValue) value;
            MyIDict<String, BufferedReader> fileTable = state.getFileTable();
            if (!fileTable.contains(fileName.getValue())) {
                BufferedReader br;
                try {
                    br = new BufferedReader(new FileReader(fileName.getValue()));
                } catch (FileNotFoundException e) {
                    throw new StmtExeException(String.format("ERROR: %s could not be opened", fileName.getValue()));
                }
                fileTable.put(fileName.getValue(), br);
                state.setFileTable(fileTable);
            } else {
                throw new StmtExeException(String.format("ERROR: %s is already opened", fileName.getValue()));
            }
        } else {
            throw new StmtExeException(String.format("ERROR: %s does not evaluate to StringType", expr.toString()));
        }
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new OpenReadFile(expr.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("OpenReadFile(%s)", expr.toString());
    }
}
