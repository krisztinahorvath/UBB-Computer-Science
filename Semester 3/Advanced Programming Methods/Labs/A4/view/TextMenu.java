package view;

import Model.adt.MyDict;
import Model.adt.MyIDict;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

import java.io.IOException;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private MyIDict<String, Command> commands;

    public TextMenu(){
        commands = new MyDict<>();
    }

    public void addCommand(Command cmd){
        commands.put(cmd.getKey(), cmd);
    }

    private void printMenu(){
        for (Command cmd: commands.values()){
            String line = String.format("%4s: %s", cmd.getKey(), cmd.getDescription());
            System.out.println(line);
        }
    }

    public void show(){
        Scanner scanner = new Scanner(System.in);
        while(true){
            printMenu();
            System.out.println("Input the option: ");
            String key = scanner.nextLine();
            try{
                Command cmd = commands.lookUp(key);
                cmd.execute();
            }
            catch (ADTException e){
                System.out.println("Invalid option!");
            } catch (StmtExeException | ExprEvalException | IOException | DivisionByZero e) {
                throw new RuntimeException(e);
            }
        }
    }
}
