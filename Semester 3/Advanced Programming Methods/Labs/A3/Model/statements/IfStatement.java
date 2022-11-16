package Model.statements;

import Model.adt.MyIStack;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.values.BoolValue;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class IfStatement implements  IStatement{
    IExpression expression;
    IStatement thenStmt;
    IStatement elseStmt;

    public IfStatement(IExpression e, IStatement thenS, IStatement elseS){
        expression = e;
        thenStmt = thenS;
        elseStmt = elseS;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        IValue result = this.expression.eval(state.getSymTable());
        if (result instanceof BoolValue boolResult) {
            IStatement statement;
            if (boolResult.getValue()) {
                statement = thenStmt;
            } else {
                statement = elseStmt;
            }

            MyIStack<IStatement> stack = state.getExeStack();
            stack.push(statement);
            state.setExeStack(stack);
            return state;
        } else {
            throw new StmtExeException("ERROR: provide a boolean expression in an if statement.");
        }
    }

    @Override
    public IStatement deepCopy() {
        return new IfStatement(expression.deepCopy(), thenStmt.deepCopy(), elseStmt.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("if(%s){%s}else{%s}", expression.toString(), thenStmt.toString(), elseStmt.toString());
    }
}
