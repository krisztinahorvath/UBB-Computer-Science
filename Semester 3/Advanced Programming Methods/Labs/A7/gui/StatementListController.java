package gui;

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
import exceptions.InterpreterException;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import service.Service;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class StatementListController implements Initializable {
    @FXML
    ListView<IStatement> statementListView;

    @FXML
    Button displayButton;
    MainWindowController mainWindowController;

    public void setMainWindowController(MainWindowController mainWindowController){
        this.mainWindowController = mainWindowController;
    }

    public MainWindowController getMainWindowController() {
        return mainWindowController;
    }

    public IStatement selectStatement(ActionEvent actionEvent){
        return  statementListView.getSelectionModel().getSelectedItem();
    }

    @FXML
    public void initialize(URL url, ResourceBundle resourceBundle){
        displayPrograms();
    }

    @FXML
    public void displayPrograms(){
        List<IStatement> initList = getAllStatements();
        statementListView.setItems(FXCollections.observableList(initList));
        statementListView.getSelectionModel().select(0);

        statementListView.setOnMouseClicked(mouseEvent -> {
            if(mouseEvent.getClickCount() == 2){
                int index = statementListView.getSelectionModel().getSelectedIndex();
                System.out.println(index);
                IStatement currentProgramSelected = statementListView.getSelectionModel().getSelectedItem();

                try{
                    currentProgramSelected.typeCheck(new MyDict<>());
                    ProgramState programState = new ProgramState(new MyStack<>(), new MyDict<>(), new MyList<>(), currentProgramSelected, new MyDict<>(), new MyHeap());
                    IRepository repo = new Repository(programState, "log" + (index + 1 ) + ".txt");
                    Service serv = new Service(repo);

                    mainWindowController.setController(serv);

                } catch(InterpreterException e){
                    Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage());
                    alert.show();
                }

            }
        });

    }

    private List<IStatement> getAllStatements() {
        List<IStatement> allStatements = new ArrayList<>();

        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));

        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement("a",new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b",new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression('*',new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));

        IStatement ex4 = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(new OpenReadFile(new VariableExpression("varf")),
                                new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(new ReadFile(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(new ReadFile(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseReadFile(new VariableExpression("varf"))))))))));

        IStatement ex5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new IntValue(5))),
                                new CompoundStatement(new AssignStatement("b", new ValueExpression(new IntValue(7))),
                                        new IfStatement(new RelationalExpression(">", new VariableExpression("a"),
                                                new VariableExpression("b")),new PrintStatement(new VariableExpression("a")),
                                                new PrintStatement(new VariableExpression("b")))))));

        IStatement ex6 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));

        IStatement ex7 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)))))))));

        IStatement ex8 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement( new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompoundStatement(new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression('+', new ReadHeapExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5))))))));

        IStatement ex9 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new NewStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a")))))))));

        IStatement ex10 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))),
                        new CompoundStatement(new WhileStatement(new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(0))),
                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignStatement("v",new ArithmeticExpression('-', new VariableExpression("v"), new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));

        IStatement ex11 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new RefType(new IntType())),
                        new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new NewStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(new CompoundStatement(new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))))))));
        allStatements.add(ex1);
        allStatements.add(ex2);
        allStatements.add(ex3);
        allStatements.add(ex4);
        allStatements.add(ex5);
        allStatements.add(ex6);
        allStatements.add(ex7);
        allStatements.add(ex8);
        allStatements.add(ex9);
        allStatements.add(ex10);
        allStatements.add(ex11);

        return allStatements;
    }
}
