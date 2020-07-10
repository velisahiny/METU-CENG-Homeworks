package grt;

public class Sym implements MathExpression {
    private String value;

    public Sym(String value) {
        this.value = value;
    }

    @Override
    public <T> T accept(MathVisitor<T> mathVisitor) {
        return mathVisitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Sym) {
            return ((Sym) me).value.equals(value);
        }
        else return false;
    }

    public String getValue() {
        return value;
    }
}
