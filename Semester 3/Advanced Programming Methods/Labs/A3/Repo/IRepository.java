package Repo;

import Model.programState.ProgramState;
import exceptions.ADTException;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramList();
    void setProgramStates(List<ProgramState> programStates);
    ProgramState getCurrentState();
    void addProgram(ProgramState program);
    void logPrgStateExec() throws ADTException, IOException;
    void emptyLogFile() throws IOException;
}
