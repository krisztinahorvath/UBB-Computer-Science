package Model;

public class Turtle implements IAquarium{
    private int age;

    public Turtle(int age){
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
        return "Turtle, age: " + getAge();
    }
}
