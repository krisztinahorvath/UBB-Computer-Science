package gui;


import Model.adt.MyIDict;
import Model.adt.MyIList;
import Model.adt.MyIStack;
import Model.programState.ProgramState;
import Model.statements.IStatement;
import Model.values.IValue;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import service.Service;

import java.awt.event.ActionEvent;
import java.io.BufferedReader;
import java.net.URL;
import java.util.*;
import java.util.stream.Collectors;

public class MainWindowController implements Initializable {
    Service controller;

    @FXML
    TextField programStatesNrTextField;

    @FXML
    TableView<Map.Entry<Integer, IValue>> heapTableView;

    @FXML
    TableColumn<Map.Entry<Integer, IValue>,Integer> heapTableAddr;

    @FXML
    TableColumn<Map.Entry<Integer, IValue>,String> heapTableValue;

    @FXML
    ListView<String> outListView;

    @FXML
    ListView<String> fileTableListView;

    @FXML
    ListView<String> programStateIDListView;

    @FXML
    TableView<Map.Entry<String, IValue>> symTableView;

    @FXML
    TableColumn<Map.Entry<String, IValue>, String> symTableName;

    @FXML
    TableColumn<Map.Entry<String, IValue>,String> symTableValue;


    @FXML
    ListView<String> exeStackListView;

    @FXML
    Button executeButton;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        controller = null;

        heapTableAddr.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        heapTableValue.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue() + " "));

        symTableName.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey() + " "));
        symTableValue.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue() + " "));

        programStateIDListView.setOnMouseClicked(mouseEvent -> changeProgramStateHandler(getSelectedProgramState()));

    }

    public void setController(Service controller) {
        this.controller = controller;
        populateProgramStatesNr();
        populateProgramStateID();
        executeButton.setDisable(false);
    }

    public Service getController(){
        return controller;
    }

    private void  populateProgramStatesNr(){
        programStatesNrTextField.setText("Nr of program states: " + controller.getRepo().getProgramList().size());
    }

    private void populateProgramStateID(){
        List<Integer> prgStateID = controller.getRepo().getProgramList().stream()
                .map(ProgramState::getId).toList();
        List<String> prgID = new ArrayList<>();
        for(Integer stmt: prgStateID){
            prgID.add(stmt.toString());
        }
        programStateIDListView.setItems(FXCollections.observableArrayList(prgID));
        programStateIDListView.refresh();

//        programStateIDListView.setItems(FXCollections.observableArrayList(controller.getRepo().getProgramList().stream()
//                .map(ProgramState::getId)
//                .collect(Collectors.toList()).toString()));
//        programStateIDListView.refresh();
    }

    private void populateHeapTableView(ProgramState givenProgramState){
        heapTableView.setItems(FXCollections.observableList(new ArrayList<>(givenProgramState.getHeap().getContent().entrySet())));
        heapTableView.refresh();
    }

    private void populateOutListView(ProgramState giveProgramState){
        MyIList<IValue> out = giveProgramState.getOut();
        List<String> outOutput = new ArrayList<>();
        for(IValue stmt: out.getList()){
            outOutput.add(stmt.toString());
        }
        outListView.setItems(FXCollections.observableArrayList(outOutput));

//        outListView.setItems(FXCollections.observableArrayList(giveProgramState.getOut().getList().toString()));
    }

    private void populateFileTableListView(ProgramState givenProgramState){
        MyIDict<String, BufferedReader> fileTable = givenProgramState.getFileTable();
        List<String> FileTableOutput = new ArrayList<>(fileTable.getContent().keySet());
        fileTableListView.setItems(FXCollections.observableArrayList(FileTableOutput));
//        fileTableListView.setItems(FXCollections.observableArrayList(givenProgramState.getFileTable().getContent().keySet()));
    }

    private void populateSymTableView(ProgramState givenProgramState){
        symTableView.setItems(FXCollections.observableList(new ArrayList<>(givenProgramState.getSymTable().getContent().entrySet())));
        symTableView.refresh();
    }

    private void populateExeStackListView(ProgramState givenProgramState){
        MyIStack<IStatement> stack = givenProgramState.getExeStack();
        List<String> stackOutput = new ArrayList<>();
        for(IStatement stmt: stack.getStack()){
            stackOutput.add(stmt.toString());
        }
        Collections.reverse(stackOutput); // todo????
        exeStackListView.setItems(FXCollections.observableArrayList(stackOutput));
    }

    private ProgramState getSelectedProgramState(){
        if(programStateIDListView.getSelectionModel().getSelectedIndex() == -1){
            return null;
        }

        int id = programStateIDListView.getSelectionModel().getSelectedIndex();
        return controller.getRepo().getProgramStateWithID(id);
    }

    private void changeProgramStateHandler(ProgramState currentProgramState){
        if (currentProgramState == null)
            return;

        populateProgramStatesNr();
        populateProgramStateID();
        populateHeapTableView(currentProgramState);
        populateOutListView(currentProgramState);
        populateFileTableListView(currentProgramState);
        populateExeStackListView(currentProgramState);
        populateSymTableView(currentProgramState);
    }

//    @FXML
//    public void oneStepHandler(ActionEvent actionEvent){
//        if (controller == null){
//            Alert error = new Alert(Alert.AlertType.ERROR, "No program selected");
//            error.show();
//            executeButton.setDisable(true);
//            return;
//        }
//
//        ProgramState programState = getSelectedProgramState();
//
//        if(programState != null && !programState.isNotCompleted()){
//            Alert error = new Alert(Alert.AlertType.ERROR, "Nothing to execute");
//            error.show();
//            return;
//        }
//
//        try{
//            controller.oneStep();
//            changeProgramStateHandler(programState);
//            if(controller.getRepo().getProgramList().size() == 0)
//                executeButton.setDisable(true);
//        } catch (Exception e){
//            Alert error = new Alert(Alert.AlertType.ERROR, e.getMessage());
//            error.show();
//            executeButton.setDisable(true);
//        }
//
//    }

    public void oneStepHandler(javafx.event.ActionEvent actionEvent) {
        if (controller == null){
            Alert error = new Alert(Alert.AlertType.ERROR, "No program selected");
            error.show();
            executeButton.setDisable(true);
            return;
        }

        ProgramState programState = getSelectedProgramState();

        if(programState != null && programState.isNotCompleted()){
            Alert error = new Alert(Alert.AlertType.ERROR, "Nothing to execute");
            error.show();
            return;
        }

        try{
            controller.oneStep();
            changeProgramStateHandler(programState);
            if(controller.getRepo().getProgramList().size() == 0)
                executeButton.setDisable(true);
        } catch (Exception e){
            Alert error = new Alert(Alert.AlertType.ERROR, e.getMessage());
            error.show();
            executeButton.setDisable(true);
        }

    }
}
