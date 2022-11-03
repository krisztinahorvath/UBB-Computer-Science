import Service.Service;
import Repo.Repository;
import View.View;
import Service.MyException;

public class Main {
    public static void main(String[] args) throws MyException {
        Repository repo = new Repository();
        Service serv = new Service(repo);

        serv.add("fish", 2);
        serv.add("turtle", 3);
        serv.add("turtle", 1);

        View view = new View(serv);
        try{
            view.start();
        }
        catch (IndexOutOfBoundsException ex){
            System.out.println("Fixed array error!");
        }
    }
}