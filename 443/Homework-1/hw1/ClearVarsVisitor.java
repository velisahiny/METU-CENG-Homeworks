package hw1;
/*2.3.3 ClearVarsVisitor implements MathVisitor<Void>
Let visitor be of this type. Let me be a MathExpression.
Calling me.accept(visitor) should call setPreviousMatch(null) in all rule variables.*/
public class ClearVarsVisitor implements MathVisitor<Void> {

    @Override
    public Void visit(Op op) {
        MathExpression first = op.getFirst() ;
        MathExpression second =op.getSecond();
        first.accept(this);
        second.accept(this);
        return null;
    }

    @Override
    public Void visit(Num num) {
        return null;
    }
    @Override
    public Void visit(Sym sym) {
        return null;
    }
    @Override
    public Void visit(Var var) {
        var.setPreviousMatch(null);
        return null;
    }
}
