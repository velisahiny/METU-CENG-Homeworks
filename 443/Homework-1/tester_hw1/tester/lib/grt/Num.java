package grt;

public class Num implements MathExpression {
    private int value;

    public Num(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    @Override
    public <T> T accept(MathVisitor<T> mathVisitor) {
        return mathVisitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Num) {
            return ((Num) me).value == value;
        }
        else return false;
    }
}
