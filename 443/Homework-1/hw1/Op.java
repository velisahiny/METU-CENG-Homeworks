package hw1;
//A mathematical operator, holds two expressions inside as first and the second term. It should have the following:
public class Op implements MathExpression {
    private String operand;
    private MathExpression first;
    private MathExpression second;
    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }
    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Op){
            Op op  = (Op) me;
            return this.operand==op.operand && first.match(op.first) && second.match(op.second);
        }
        return false;
    }


    /** The operand can be
     "+","*","/","|-", representing addition, multiplication, division, and entails respectively. You can safely
     assume first and second as non-null.*/
    public Op(String operand, MathExpression first, MathExpression second ){
        this.operand =operand;
        this.first = first;
        this.second = second;
    }
    //Public getters.
    public String getOperand(){
        return this.operand;
    }
    public MathExpression getFirst(){
        return this.first;
    }
    public MathExpression getSecond() {
        return this.second;
    }
}
