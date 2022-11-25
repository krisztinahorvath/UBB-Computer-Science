package service;

import Model.adt.MyIStack;
import Model.programState.ProgramState;
import Model.statements.IStatement;
import Model.values.IValue;
import Model.values.RefValue;
import Repo.IRepository;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

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

    public List<Integer> getAddrFromSymTable(Collection<IValue> symTableValues){
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<Integer> getAddrFromHeap(Collection<IValue> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(e -> ( symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    public void allSteps() throws ExprEvalException, StmtExeException, ADTException, DivisionByZero, IOException {
        ProgramState prg = repository.getCurrentState();
        repository.logPrgStateExec();
        showStep();
        while(!prg.getExeStack().isEmpty()){
            oneStep(prg);
            repository.logPrgStateExec();

            prg.getHeap().setContent((HashMap<Integer, IValue>) safeGarbageCollector(
                    getAddrFromSymTable(prg.getSymTable().getContent().values()), getAddrFromHeap(prg.getHeap().getContent().values()),
                    prg.getHeap().getContent()));
            
            repository.logPrgStateExec();
            showStep();
        }
    }
}