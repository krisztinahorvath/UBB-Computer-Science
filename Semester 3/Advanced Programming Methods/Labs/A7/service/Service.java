package service;

import Model.programState.ProgramState;
import Model.values.IValue;
import Model.values.RefValue;
import Repo.IRepository;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Service {
    IRepository repository;
    boolean printStep = false;

    ExecutorService executorService;

    public Service(IRepository repo){
        repository = repo;
    }

    public void addProgramState(ProgramState programState){
        repository.addProgram(programState);
    }

    public void changePrintStep(boolean v){
        printStep = v;
    }

    public IRepository getRepo(){
        return repository;
    }

    public List<ProgramState> removeCompletedProgram(List<ProgramState> inPrgList){
        return inPrgList.stream().filter(p -> !p.isNotCompleted()).collect(Collectors.toList());
    }

//    public ProgramState oneStep(ProgramState prgState) throws ExprEvalException, StmtExeException, ADTException, DivisionByZero {
//        MyIStack<IStatement> stk = prgState.getExeStack();
//        if(stk.isEmpty())
//            throw new StmtExeException("ERROR: EMPTY PROGRAM STATE!");
//
//        IStatement thisStmt = stk.pop();
//        prgState.setExeStack(stk);
//
//        return thisStmt.execute(prgState);
//    }

    private void showStep(ProgramState programState){
        if(printStep)
            System.out.println(programState.toString());
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

    public void oneStepForAllPrograms(List<ProgramState> programStates) throws InterruptedException {
        programStates.forEach(programState -> {
            try{
                repository.logPrgStateExec(programState);
                showStep(programState);
            } catch (IOException | ADTException e){
                System.out.println(e.getMessage());
            }
        });

        List<Callable<ProgramState>> callableList = programStates.stream()
                .map((ProgramState p) -> (Callable <ProgramState>) (p::oneStep))
                .collect(Collectors.toList());

        List<ProgramState> newProgramList = executorService.invokeAll(callableList).stream()
                .map(future -> {
                    try{
                        return future.get();
                    } catch (ExecutionException | InterruptedException e){
                        System.out.println(e.getMessage());
                    }
                    return null;
                }).filter(Objects::nonNull)
                .collect(Collectors.toList());

        programStates.addAll(newProgramList);

        programStates.forEach(programState -> {
            try{
                repository.logPrgStateExec(programState);
                showStep(programState);
            } catch (IOException | ADTException e){
                System.out.println(e.getMessage());
            }
        });

        repository.setProgramList(programStates);
    }


    public void allSteps() throws ExprEvalException, StmtExeException, ADTException, DivisionByZero, IOException, InterruptedException {
        executorService = Executors.newFixedThreadPool(2);

        /// remove the completed programs
        List<ProgramState> prgList = removeCompletedProgram(repository.getProgramList());

        while(prgList.size() > 0){
            conservativeGarbageCollector(prgList);
            oneStepForAllPrograms(prgList);
            prgList = removeCompletedProgram(repository.getProgramList());
        }

        executorService.shutdownNow();

        // HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        // setPrgList of repository in order to change the repository

        // update the repository state

        repository.setProgramList(prgList);

    }

    public void conservativeGarbageCollector(List<ProgramState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymTable().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());

        programStates.forEach(p -> {
            p.getHeap().setContent((HashMap<Integer, IValue>) safeGarbageCollector(symTableAddresses, getAddrFromHeap(p.getHeap().getContent().values()), p.getHeap().getContent()));
        });
    }

    public List<ProgramState> getUnfinishedPrograms(){
        return removeCompletedProgram(repository.getProgramList());
    }

    public void oneStep() throws InterruptedException {
        executorService = Executors.newFixedThreadPool(2);

        List<ProgramState> programStates = getUnfinishedPrograms();

        oneStepForAllPrograms(programStates);
        conservativeGarbageCollector(programStates);
        programStates = getUnfinishedPrograms();

        executorService.shutdownNow();

        repository.setProgramList(programStates);

    }

}