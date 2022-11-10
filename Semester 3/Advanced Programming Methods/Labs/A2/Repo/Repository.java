package Repo;

import Model.programState.ProgramState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> programStates;
    private int currentPosition;

    public Repository(ProgramState prg){
        programStates = new ArrayList<>();
        currentPosition = 0;
        addProgram(prg);
    }

    public int getCurrentPosition() {
        return currentPosition;
    }

    public void setCurrentPosition(int currPos) {
        this.currentPosition = currPos;
    }

    @Override
    public List<ProgramState> getProgramList() {
        return programStates;
    }

    @Override
    public void setProgramStates(List<ProgramState> prgSts) {
        programStates = prgSts;
    }

    @Override
    public ProgramState getCurrentState() {
        return this.programStates.get(this.currentPosition);
    }

    @Override
    public void addProgram(ProgramState program) {
        programStates.add(program);
    }
}
