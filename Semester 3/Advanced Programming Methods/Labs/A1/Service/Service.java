package Service;

import Model.Fish;
import Model.IAquarium;
import Model.Turtle;
import Repo.IRepository;

import java.util.Objects;



public class Service {
    private IRepository repo;

    public Service(IRepository r){
        repo = r;
    }

    public void add(String name, int age) throws MyException {
        if(Objects.equals(name, "fish") && age > 0){
            Fish f = new Fish(age);
            repo.add(f);
        }
        else if(Objects.equals(name, "turtle") && age > 0){
            Turtle t = new Turtle(age);
            repo.add(t);
        }
        else
            throw new MyException("Incorrect animal breed!/Positive age needed!");
    }

    public void remove(int i) throws MyException {
        if(i < 0 || i > repo.getSize())
            throw new MyException("Index out of bounds!");
        repo.remove(i);
    }

    public IAquarium[] getOlderCreatures(){
        IAquarium[] newAquarium = new IAquarium[repo.getSize()];
        int i = 0;
        for(IAquarium creature: repo.getCreatures())
            if(creature != null && creature.getAge() > 1)
                newAquarium[i++] = creature;

        /// the array without null elements
        IAquarium[] finalAquarium = new IAquarium[i];
        System.arraycopy(newAquarium,0, finalAquarium, 0, i);

        return finalAquarium;
    }

    public IAquarium[] getAll(){
        return repo.getCreatures();
    }

    public int getSize(){
        return repo.getSize();
    }
}
