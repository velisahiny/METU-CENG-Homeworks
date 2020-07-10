package hw1;
/*DocElement classes
These are essentially just here to print pretty HTML documents. All the concrete classes here should
implement DocElement and call visit methods of their visitors in their accept methods with this as
the argument.
*/
public interface DocElement {
    //Only has the accept method for its sibling visitor TextVisitor:
    <T> T accept(TextVisitor<T> visitor);
}
