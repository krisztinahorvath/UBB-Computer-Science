package view;

import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.IOException;

public abstract class Command {
    private String key, description;

    public Command(String k, String d) {
        key = k;
        description = d;
    }

    public abstract void execute() throws StmtExeException, DivisionByZero, ADTException, IOException, ExprEvalException;

    public String getKey() {return key;}

    public String getDescription() {return description;}

}
