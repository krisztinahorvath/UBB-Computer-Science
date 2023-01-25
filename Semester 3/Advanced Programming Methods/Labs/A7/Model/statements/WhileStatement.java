package Model.statements;

import Model.adt.MyIDict;
import Model.adt.MyIStack;
import Model.expressions.IExpression;
import Model.programState.ProgramState;
import Model.types.BoolType;
import Model.types.IType;
import Model.values.BoolValue;
import Model.values.IValue;
import exceptions.ADTException;
import exceptions.DivisionByZero;
import exceptions.ExprEvalException;
import exceptions.StmtExeException;

public class WhileStatement implements IStatement{
    private final IExpression expression;
    private final IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement){
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StmtExeException, ExprEvalException, ADTException, DivisionByZero {
        IValue value = expression.eval(state.getSymTable(), state.getHeap());
        MyIStack<IStatement> stack = state.getExeStack();

        if(!value.getType().equals(new BoolType()))
            throw new StmtExeException(String.format("%s is not of BoolType", value));

        BoolValue boolValue = (BoolValue) value;
        if(boolValue.getValue()){
            stack.push(this);
            stack.push(statement);
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(expression.deepCopy(), statement.deepCopy());
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws StmtExeException, ExprEvalException, ADTException {
        IType typeExpr = expression.typeCheck(typeEnv);
        if (typeExpr.equals(new BoolType())) {
            statement.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        } else
            throw new StmtExeException("The condition of WHILE does not have the type Bool.");
    }

    @Override
    public String toString(){
        return String.format("while(%s) { %s }", expression, statement);
    }
}
