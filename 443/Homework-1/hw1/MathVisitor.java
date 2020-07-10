package hw1;
/*2.3.1 MathVisitor<T> interface
It should have the following:
*/
public interface MathVisitor<T> {
    T visit(Op op);
    T visit(Num num);
    T visit(Sym sym);
    T visit(Var var);
}
