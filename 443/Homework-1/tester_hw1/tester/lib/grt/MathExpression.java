package grt;

public interface MathExpression {
    <T> T accept(MathVisitor<T> mathVisitor);
    boolean match(MathExpression me);
}
