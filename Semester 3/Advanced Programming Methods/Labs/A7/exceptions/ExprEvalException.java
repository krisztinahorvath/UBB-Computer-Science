package exceptions;

public class ExprEvalException extends InterpreterException {
    public ExprEvalException() {
        super();
    }

    public ExprEvalException(String msg) {
        super(msg);
    }
}
