package Model.programState;

import Model.adt.MyIDict;
import Model.adt.MyIList;
import Model.adt.MyIStack;
import Model.statements.IStatement;
import Model.values.IValue;
import exceptions.ADTException;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDict<String, IValue> symTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;

    public ProgramState(MyIStack<IStatement> stack, MyIDict<String, IValue> symTbl, MyIList<IValue> _out, IStatement program){
        exeStack = stack;
        symTable = symTbl;
        out = _out;
        originalProgram = program.deepCopy();
        exeStack.push(originalProgram);
    }

    public void setExeStack(MyIStack<IStatement> newStack) {
        this.exeStack = newStack;
    }

    public void setSymTable(MyIDict<String, IValue> newSymTable) {
        this.symTable = newSymTable;
    }

    public void setOut(MyIList<IValue> newOut) {
        this.out = newOut;
    }

    public MyIStack<IStatement> getExeStack(){
        return  exeStack;
    }

    public MyIDict<String, IValue> getSymTable(){
        return symTable;
    }

    public MyIList<IValue> getOut(){
        return out;
    }

    public String exeStackToString() {
        StringBuilder exeStackString = new StringBuilder();
        for (IStatement elem : exeStack) {
            exeStackString.append("[ ").append(elem.toString()).append(" ]\n");
        }
        return exeStackString.toString();
    }

    public String symTableToString() throws ADTException {
        StringBuilder symTableString = new StringBuilder();
        for (String key: symTable.keySet()) {
            symTableString.append(String.format("%s -> %s\n", key, symTable.lookUp(key).toString()));
        }
        return symTableString.toString();
    }

    public String outToString() {
        StringBuilder outString = new StringBuilder();
        for (IValue elem: out.getList()) {
            outString.append(String.format("%s\n", elem.toString()));
        }
        return outString.toString();
    }

    @Override
    public String toString() {
        try {
            return "Execution stack: \n" + exeStackToString() + "Symbol table: \n" + symTableToString() + "Output list: \n" + outToString();
        } catch (ADTException e) {
            throw new RuntimeException(e);
        }
    }
}
