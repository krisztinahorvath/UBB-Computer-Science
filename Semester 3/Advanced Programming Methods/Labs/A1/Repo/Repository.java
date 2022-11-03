package Repo;

import Model.IAquarium;

public class Repository implements IRepository{
    private IAquarium[] aquarium;
    private int size;

    public Repository() {
        aquarium = new IAquarium[20];
        size = 0;
    }

    @Override
    public void add(IAquarium aq) {
        this.aquarium[size] = aq;
        size++;
    }

    @Override
    public void remove(int i) {
        IAquarium[] newAquarium = new IAquarium[size - 1];
        int j = 0;
        for(int k = 0; k < size; k++)
        {
            if(k != i){
                newAquarium[j] = aquarium[k];
                j++;
            }
        }

        aquarium = newAquarium;
        size--;
    }

    @Override
    public IAquarium[] getCreatures() {
        return aquarium;
    }

    @Override
    public int getSize() {
        return size;
    }
}
