package Model.programState;

import Model.adt.MyIDict;
import Model.adt.MyIList;
import Model.adt.MyIStack;
import Model.statements.IStatement;
import Model.values.IValue;
import exceptions.ADTException;
import view.Command;

import java.io.BufferedReader;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDict<String, IValue> symTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;
    private MyIDict<String, BufferedReader> fileTable;

    public ProgramState(MyIStack<IStatement> stack, MyIDict<String, IValue> symTbl, MyIList<IValue> _out, IStatement program, MyIDict<String, BufferedReader> fileTbl){
        exeStack = stack;
        symTable = symTbl;
        out = _out;
        originalProgram = program.deepCopy();
        fileTable = fileTbl;
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

    public void setFileTable(MyIDict<String, BufferedReader> newFileTable) {fileTable = newFileTable;}

    public MyIStack<IStatement> getExeStack(){
        return  exeStack;
    }

    public MyIDict<String, IValue> getSymTable(){
        return symTable;
    }

    public MyIList<IValue> getOut(){
        return out;
    }

    public MyIDict<String, BufferedReader> getFileTable() {return fileTable;}

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

    public String fileTableToString() {
        StringBuilder fileTableStringBuilder = new StringBuilder();
        for (String key: fileTable.keySet()) {
            fileTableStringBuilder.append(String.format("%s\n", key));
        }
        return fileTableStringBuilder.toString();
    }

    @Override
    public String toString() {
        try {
            return "Execution stack: \n" + exeStackToString() + "Symbol table: \n" + symTableToString() + "Output list: \n" + outToString() + "File table:\n" + fileTableToString();
        } catch (ADTException e) {
            throw new RuntimeException(e);
        }
    }

    public String programStateToString() throws ADTException {
        return "Execution stack: \n" + exeStackToString() + "Symbol table: \n" + symTableToString() + "Output list: \n" + outToString() + "File table:\n" + fileTableToString();
    }



}
