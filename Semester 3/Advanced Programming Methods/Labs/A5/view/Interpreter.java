package view;

import Model.adt.MyDict;
import Model.adt.MyHeap;
import Model.adt.MyList;
import Model.adt.MyStack;
import Model.expressions.*;
import Model.programState.ProgramState;
import Model.statements.*;
import Model.types.BoolType;
import Model.types.IntType;
import Model.types.RefType;
import Model.types.StringType;
import Model.values.BoolValue;
import Model.values.IntValue;
import Model.values.StringValue;
import Repo.IRepository;
import Repo.Repository;
import service.Service;

public class Interpreter {
    public static void main(String[] args){
        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        ProgramState prg1 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex1,  new MyDict<>(), new MyHeap());
        IRepository repo1 = new Repository(prg1, "zfiles/log1.txt");
        Service service1 = new Service(repo1);

        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement("a",new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b",new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression('*',new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        ProgramState prg2 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex2, new MyDict<>(), new MyHeap());
        IRepository repo2 = new Repository(prg2, "zfiles/log2.txt");
        Service service2 = new Service(repo2);

        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
        ProgramState prg3 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex3,  new MyDict<>(), new MyHeap());
        IRepository repo3 = new Repository(prg3, "zfiles/log3.txt");
        Service service3 = new Service(repo3);

        IStatement ex4 = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(new OpenReadFile(new VariableExpression("varf")),
                                new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(new ReadFile(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(new ReadFile(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseReadFile(new VariableExpression("varf"))))))))));

        ProgramState prg4 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex4, new MyDict<>(), new MyHeap());
        IRepository repo4 = new Repository(prg4, "zfiles/log4.txt");
        Service service4 = new Service(repo4);

        IStatement ex5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new IntValue(5))),
                                new CompoundStatement(new AssignStatement("b", new ValueExpression(new IntValue(7))),
                                        new IfStatement(new RelationalExpression(">", new VariableExpression("a"),
                                                new VariableExpression("b")),new PrintStatement(new VariableExpression("a")),
                                                new PrintStatement(new VariableExpression("b")))))));

        ProgramState prg5 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex5, new MyDict<>(), new MyHeap());
        IRepository repo5 = new Repository(prg5, "zfiles/log5.txt");
        Service service5 = new Service(repo5);


        IStatement ex6 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));
        ProgramState prg6 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex6, new MyDict<>(), new MyHeap());
        IRepository repo6 = new Repository(prg6, "zfiles/log6.txt");
        Service service6 = new Service(repo6);

        IStatement ex7 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)))))))));
        ProgramState prg7 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex7,  new MyDict<>(), new MyHeap());
        IRepository repo7 = new Repository(prg7, "zfiles/log7.txt");
        Service service7 = new Service(repo7);

        IStatement ex8 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement( new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompoundStatement(new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression('+', new ReadHeapExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5))))))));

        ProgramState prg8 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex8, new MyDict<>(), new MyHeap());
        IRepository repo8 = new Repository(prg8, "zfiles/log8.txt");
        Service service8 = new Service(repo8);

        IStatement ex9 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a")))))))));

        ProgramState prg9 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex9, new MyDict<>(), new MyHeap());
        IRepository repo9 = new Repository(prg9, "zfiles/log9.txt");
        Service service9 = new Service(repo9);

        IStatement ex10 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))),
                        new CompoundStatement(new WhileStatement(new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(0))),
                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignStatement("v",new ArithmeticExpression('-', new VariableExpression("v"), new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));

        ProgramState prg10 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex10, new MyDict<>(), new MyHeap());
        IRepository repo10 = new Repository(prg10, "zfiles/log10.txt");
        Service service10 = new Service(repo10);


        IStatement ex11 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new IntType())),
                        new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new NewStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(new CompoundStatement(new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))))))));

        ProgramState prg11 = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), ex11, new MyDict<>(), new MyHeap());
        IRepository repo11 = new Repository(prg11, "zfiles/log11.txt");
        Service service11 = new Service(repo11);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand(0, "exit"));
        menu.addCommand(new RunExampleCommand(1, ex1.toString(), service1));
        menu.addCommand(new RunExampleCommand(2, ex2.toString(), service2));
        menu.addCommand(new RunExampleCommand(3, ex3.toString(), service3));
        menu.addCommand(new RunExampleCommand(4, ex4.toString(), service4));
        menu.addCommand(new RunExampleCommand(5, ex5.toString(), service5));
        menu.addCommand(new RunExampleCommand(6, ex6.toString(), service6)); /// A4
        menu.addCommand(new RunExampleCommand(7, ex7.toString(), service7));
        menu.addCommand(new RunExampleCommand(8, ex8.toString(), service8));
        menu.addCommand(new RunExampleCommand(9, ex9.toString(), service9));
        menu.addCommand(new RunExampleCommand(10, ex10.toString(), service10));
        menu.addCommand(new RunExampleCommand(11, ex11.toString(), service11));

        menu.show();
    }
}
