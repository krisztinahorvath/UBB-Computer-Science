package Model.statements;

import Model.adt.MyIDict;
import Model.programState.ProgramState;
import Model.types.IType;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class VariableDeclarationStatement implements IStatement{
    String name;
    IType type;

    public VariableDeclarationStatement(String n, IType t){
        name = n;
        type = t;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException {
        MyIDict<String, IValue> symTable = state.getSymTable();
        if (symTable.contains(name))
            throw new StmtExeException(String.format("ERROR: %s already exists in the symTable", name));
        symTable.put(name, type.defaultValue());
        state.setSymTable(symTable);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new VariableDeclarationStatement(name, type);
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException {
        typeEnv.put(name, type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return String.format("%s %s", type.toString(), name);
    }
}
