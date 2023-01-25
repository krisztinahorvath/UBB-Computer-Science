package gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader programListLoader = new FXMLLoader();
        programListLoader.setLocation(getClass().getResource("/resources/StatementListController.fxml"));

        Parent programListParent = programListLoader.load();

        StatementListController statementListController = programListLoader.getController();

        Scene primaryScene = new Scene(programListParent);

        Stage primaryStage = new Stage();
        primaryStage.setTitle("List of programs");
        primaryStage.setScene(primaryScene);
        primaryStage.show();


        FXMLLoader programExecutorLoader = new FXMLLoader();
        programExecutorLoader.setLocation(getClass().getResource("/resources/ProgramExecutorController.fxml"));

        Parent programExecutorParent = programExecutorLoader.load();

        MainWindowController mainWindowController = programExecutorLoader.getController();

        statementListController.setMainWindowController(mainWindowController);

        Stage secondaryStage = new Stage();
        secondaryStage.setTitle("Interpreter");
        secondaryStage.setScene(new Scene(programExecutorParent, 700, 500));
        secondaryStage.show();
    }
}
