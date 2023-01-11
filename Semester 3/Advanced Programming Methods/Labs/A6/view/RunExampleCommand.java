package view;

import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;
import service.Service;

import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class RunExampleCommand extends Command{
    private Service serv;

    public RunExampleCommand(int k, String d, Service s) {
        super(k, d);
        serv = s;
    }

    @Override
    public void execute() {
        try{
            System.out.print("Print steps?(y/n) ");
            Scanner scn = new Scanner(System.in);
            String cmd = scn.next();
            serv.changePrintStep(Objects.equals(cmd, "y"));
            serv.allSteps();
        }
        catch (ExprEvalException | ADTException | StmtExeException | DivisionByZero | IOException e){
            System.out.println(e.getMessage());
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
