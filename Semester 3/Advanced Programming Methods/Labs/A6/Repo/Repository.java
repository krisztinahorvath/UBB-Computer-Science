package Repo;

import Model.programState.ProgramState;
import exceptions.ADTException;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> programStates;
    private final String logFilePath;

    public Repository(ProgramState prg, String logFilePath){
        programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
        addProgram(prg);
    }

    @Override
    public List<ProgramState> getProgramList() {
        return programStates;
    }

    @Override
    public void setProgramList(List<ProgramState> prgSts) {
        programStates = prgSts;
    }

//    @Override
//    public ProgramState getCurrentState() {
//        return this.programStates.get(this.currentPosition);
//    }

    @Override
    public void addProgram(ProgramState program) {
        programStates.add(program);
    }

    @Override
    public void logPrgStateExec(ProgramState programState) throws ADTException, IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.println(programState.programStateToString());
        logFile.close();
    }

    @Override
    public void emptyLogFile() throws IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)));
        logFile.close();
    }
}
