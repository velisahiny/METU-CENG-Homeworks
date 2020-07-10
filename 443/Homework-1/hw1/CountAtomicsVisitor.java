package hw1;
/*2.3.2 CountAtomicsVisitor implements MathVisitor<Integer>
Let visitor be of this type. Let me be a MathExpression. Calling me.accept(visitor) should return the how
many atomics there are (Sym,Var,Num) in me.*/
public class CountAtomicsVisitor implements MathVisitor<Integer>{


    @Override
    public Integer visit(Op op) {
        int sum=0;
        MathExpression first = op.getFirst() ;
        MathExpression second =op.getSecond();
        sum+=first.accept(this);
        sum+=second.accept(this);
        return sum;
    }

    @Override
    public Integer visit(Num num) {
        return 1;
    }

    @Override
    public Integer visit(Sym sym) {
        return 1;
    }

    @Override
    public Integer visit(Var var) {
        return 1;
    }
}
