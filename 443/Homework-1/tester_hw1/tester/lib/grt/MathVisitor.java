package grt;

public interface MathVisitor<T> {
    T visit(Num num);
    T visit(Op op);
    T visit(Sym sym);
    T visit(Var var);
}
