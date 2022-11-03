package Repo;
import Model.IAquarium;

public interface IRepository {
    void add(IAquarium aq);
    void remove(int i);
    IAquarium[] getCreatures();
    int getSize();

}
