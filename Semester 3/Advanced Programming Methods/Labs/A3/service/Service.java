package service;

import Model.adt.MyIStack;
import Model.programState.ProgramState;
import Model.statements.IStatement;
import Repo.IRepository;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.IOException;

public class Service {
    IRepository repository;
    boolean printStep = false;

    public Service(IRepository repo){
        repository = repo;
    }

    public void changePrintStep(boolean v){
        printStep = v;
    }

    public ProgramState oneStep(ProgramState prgState) throws ExprEvalException, StmtExeException, ADTException, DivisionByZero {
        MyIStack<IStatement> stk = prgState.getExeStack();
        if(stk.isEmpty())
            throw new StmtExeException("ERROR: EMPTY PROGRAM STATE!");

        IStatement thisStmt = stk.pop();
        prgState.setExeStack(stk);

        return thisStmt.execute(prgState);
    }

    private void showStep(){
        if(printStep)
            System.out.println(repository.getCurrentState().toString());
    }

    public void allSteps() throws ExprEvalException, StmtExeException, ADTException, DivisionByZero, IOException {
        ProgramState prg = repository.getCurrentState();
        repository.logPrgStateExec();
        showStep();
        while(!prg.getExeStack().isEmpty()){
            oneStep(prg);
            repository.logPrgStateExec();
            showStep();
        }
    }
}
