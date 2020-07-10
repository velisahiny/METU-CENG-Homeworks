package grt;

public class CountAtomicsVisitor2 implements MathVisitor<Integer> {
    @Override
    public Integer visit(Num num) {
        return 1;
    }

    @Override
    public Integer visit(Op op) {
        return op.getFirst().accept(this)+op.getSecond().accept(this);
    }

    @Override
    public Integer visit(Sym sym) {
        return 1;
    }

    @Override
    public Integer visit(Var var) {
        return var.getPreviousMatch() == null?1:1+var.getPreviousMatch().accept(this);
    }
}
