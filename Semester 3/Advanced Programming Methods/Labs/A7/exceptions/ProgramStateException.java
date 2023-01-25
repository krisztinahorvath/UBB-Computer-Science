package exceptions;

public class ProgramStateException extends InterpreterException{
    public ProgramStateException() {super();}

    public ProgramStateException(String msg) {super(msg);}
}
