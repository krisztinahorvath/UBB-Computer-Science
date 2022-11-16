package view;

import Model.adt.*;
import Model.expressions.ArithmeticExpression;
import Model.expressions.ValueExpression;
import Model.expressions.VariableExpression;
import Model.programState.ProgramState;
import Model.statements.*;
import Model.types.BoolType;
import Model.types.IntType;
import Model.values.BoolValue;
import Model.values.IValue;
import Model.values.IntValue;
import Repo.IRepository;
import Repo.Repository;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;
import service.Service;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class View {
    private void printMenu(){
        System.out.print("\nMenu: \n" +
                "\t0. Exit\n" +
                "\t1. Run program1\n" +
                "\t2. Run program2\n" +
                "\t3. Run Program3\n " +
                "Option: ");
    }

    public void run(){
        while(true){
            try{
                printMenu();

                Scanner scn = new Scanner(System.in);
                int cmd = scn.nextInt();

                if(cmd == 0)
                    break;

                else if (cmd == 1)
                    runPrg1();

                else if (cmd == 2)
                    runPrg2();

                else if (cmd == 3)
                    runPrg3();

                else
                    System.out.println("Invalid command!");


            }
            catch (Exception ex){
                System.out.println(ex.getMessage());
            }
        }
    }

    private void runPrg1() throws StmtExeException, ADTException, ExprEvalException, DivisionByZero, IOException {
        IStatement stmt = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));

        runStatement(stmt);
    }

    private void runPrg2() throws StmtExeException, ADTException, ExprEvalException, DivisionByZero, IOException {
        IStatement stmt = new CompoundStatement(new VariableDeclarationStatement("a",new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b",new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+',
                                new ValueExpression(new IntValue(2)), new ArithmeticExpression('*',
                                new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+',
                                        new VariableExpression("a"), new ValueExpression(new IntValue(1)))),
                                        new PrintStatement(new VariableExpression("b"))))));
        runStatement(stmt);
    }

    private void runPrg3() throws StmtExeException, ADTException, ExprEvalException, DivisionByZero, IOException {
        IStatement stmt = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));

        runStatement(stmt);

    }

    private void runStatement(IStatement stmt) throws ExprEvalException, StmtExeException, ADTException, DivisionByZero, IOException {
        MyIStack<IStatement> executionStack = new MyStack<>();
        MyIDict<String, IValue> symbolTable = new MyDict<>();
        MyIList<IValue> out = new MyList<>();
        MyIDict<String, BufferedReader> fileTable = new MyDict<>();

        ProgramState programState = new ProgramState(executionStack, symbolTable, out, stmt, fileTable);

        IRepository repo = new Repository(programState, "log.txt");
        Service serv = new Service(repo);

        System.out.print("Print steps?(y/n) ");
        Scanner scn = new Scanner(System.in);
        String cmd = scn.next();
        serv.changePrintStep(Objects.equals(cmd, "y"));

        serv.allSteps();
        System.out.println("\nResult is" + programState.getOut().toString().replace('[', ' ').replace(']', ' '));
    }
}
