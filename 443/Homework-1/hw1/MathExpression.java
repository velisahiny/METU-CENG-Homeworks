package hw1;
//All the concrete classes here should implement MathExpression and call visit methods of their
// visitors in their accept methods with this as the argument.
public interface MathExpression {
    <T> T accept(MathVisitor<T> visitor);
    default boolean match(MathExpression me){
        return me instanceof MathExpression;
    } // returns true if me matches this

}
