package hw1;
/*2.2.3 EquationText class
Holds a MathExpression. It should have the following:
*/
public class EquationText implements  DocElement{
    private MathExpression innerMath;
    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }
    //public setter
    public EquationText(MathExpression innerMath){
        this.innerMath=innerMath;
    }
    //public getter
    public MathExpression getInnerMath(){
        return this.innerMath;
    }
}
