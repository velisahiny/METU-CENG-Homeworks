package grt;

public class Op implements MathExpression {
    private String operand;
    private MathExpression first;
    private MathExpression second;

    public Op(String operand, MathExpression first, MathExpression second) {
        this.operand = operand;
        this.first = first;
        this.second = second;
    }

    public MathExpression getFirst() {
        return first;
    }
    public MathExpression getSecond() {
        return second;
    }

    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Op) {
            Op op = (Op) me;
            return op.operand.equals(operand) && first.match(op.first) && second.match(op.second);
        }
        else return false;
    }

    public String getOperand() {
        return operand;
    }

    @Override
    public <T> T accept(MathVisitor<T> mathVisitor) {
        return mathVisitor.visit(this);
    }
}
