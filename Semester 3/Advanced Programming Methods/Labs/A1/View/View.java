package View;
import Model.IAquarium;
import Service.Service;
import Service.MyException;

import java.util.InputMismatchException;
import java.util.Scanner;


public class View {
    private final Service serv;

    public View(Service serv) {
        this.serv = serv;
    }

    private static void menu(){
        System.out.print("\n\nCommand:" +
                "\n0.Exit" +
                "\n1.Print all creatures" +
                "\n2.Add a creature(fish/turtle)" +
                "\n3.Remove a creature based on index" +
                "\n4.Display creatures older than a year" +
                "\nOption: ");
    }

    private void printAll(){
        IAquarium[] aq = serv.getAll();
        if(this.serv.getSize() == 0){
            System.out.println("Empty repo!");
        }
        else{
            System.out.println(" ");
            for(int i = 0; i < serv.getSize(); i++)
                System.out.println((i) + ". " + aq[i].toString());
        }
    }

    private void add(){
        System.out.print("Type: ");

        Scanner readType = new Scanner(System.in);
        String type = readType.nextLine();

        System.out.print("Age: ");
        Scanner readAge = new Scanner(System.in);

        try{
            int age = readAge.nextInt();
            serv.add(type, age);
        }
        catch (MyException | InputMismatchException ex) {
            System.out.println(ex);
        }
    }

    private void remove(){
        System.out.print("\nIndex: ");
        Scanner readIndex = new Scanner(System.in);
        try{
            int index = readIndex.nextInt();
            serv.remove(index);
        }
        catch (MyException | InputMismatchException | NegativeArraySizeException ex){
            System.out.println(ex);}
    }

    private void olderCreatures(){
        IAquarium[] aq = serv.getOlderCreatures();
        for(IAquarium creature: aq)
            System.out.println(creature.toString());
    }

    public void start(){
        while(true){
            try {
                menu();
                Scanner sc = new Scanner(System.in);
                int cmd = sc.nextInt();

                if(cmd == 1)
                    printAll();

                else if(cmd == 2)
                    add();

                else if(cmd == 3)
                    remove();

                else if(cmd == 4)
                    olderCreatures();

                else if(cmd == 0)
                    break;

                else
                    System.out.println("Invalid command");
            }
            catch (InputMismatchException ex){
                System.out.println("\nChoose an option from the menu!");
            }
        }

    }
}
