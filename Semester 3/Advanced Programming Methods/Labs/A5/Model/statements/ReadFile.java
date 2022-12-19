package Model.statements;

import Model.adt.MyIDict;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.IntType;
import Model.types.StringType;
import Model.values.IValue;
import Model.values.IntValue;
import Model.values.StringValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStatement{
    private final IExpression expr;
    private final String varName;

    public ReadFile(IExpression e, String vName){
        expr = e;
        varName = vName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        MyIDict<String, IValue> symTable = state.getSymTable();
        MyIDict<String, BufferedReader> fileTable = state.getFileTable();

        if (symTable.contains(varName)) {
            IValue value = symTable.lookUp(varName);
            if (value.getType().equals(new IntType())) {
                value = expr.eval(symTable, state.getHeap());
                if (value.getType().equals(new StringType())) {
                    StringValue castValue = (StringValue) value;
                    if (fileTable.contains(castValue.getValue())) {
                        BufferedReader br = fileTable.lookUp(castValue.getValue());
                        try {
                            String line = br.readLine();
                            if (line == null)
                                line = "0";
                            symTable.put(varName, new IntValue(Integer.parseInt(line)));
                        } catch (IOException e) {
                            throw new StmtExeException(String.format("ERROR: Could not read from file %s", castValue));
                        }
                    } else {
                        throw new StmtExeException(String.format("ERROR: The file table does not contain %s", castValue));
                    }
                } else {
                    throw new StmtExeException(String.format("ERROR: %s does not evaluate to StringType", value));
                }
            } else {
                throw new StmtExeException(String.format("ERROR: %s is not of type IntType", value));
            }
        } else {
            throw new StmtExeException(String.format("ERROR: %s is not present in the symTable.", varName));
        }
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFile(expr.deepCopy(), varName);
    }

    @Override
    public String toString() {
        return String.format("ReadFile(%s, %s)", expr.toString(), varName);
    }
}
