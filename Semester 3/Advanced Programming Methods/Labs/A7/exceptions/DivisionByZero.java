package exceptions;

public class DivisionByZero extends InterpreterException{
    public DivisionByZero() { super();}
    public DivisionByZero(String msg) {super(msg);}
}
