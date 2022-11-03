package Model;

public class Fish implements IAquarium {
    private int age;

    public Fish(int age){
        this.age = age;
    }

    @Override
    public int getAge() {
        return age;
    }

    @Override
    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString(){
        return "Fish, age: " + getAge();
    }
}
