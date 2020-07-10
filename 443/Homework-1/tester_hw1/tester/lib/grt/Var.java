package grt;

public class Var implements MathExpression {
    private int id;

    private MathExpression previousMatch;

    public Var(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public MathExpression getPreviousMatch() {
        return previousMatch;
    }

    public void setPreviousMatch(MathExpression previousMatch) {
        this.previousMatch = previousMatch;
    }

    @Override
    public boolean match(MathExpression me) {
        if(previousMatch == null) {
            setPreviousMatch(me);
            return true;
        }
        else return getPreviousMatch().match(me);
    }

    @Override
    public <T> T accept(MathVisitor<T> mathVisitor) {
        return mathVisitor.visit(this);
    }
}
