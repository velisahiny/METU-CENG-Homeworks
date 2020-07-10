package hw1;


//Represents a number. It should have the following:
public class Num implements MathExpression{
    private int value;
    @Override
    public <T> T accept(MathVisitor<T>  visitor) {
        return visitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Num){
            return ((Num) me).getValue()==value;
        }
        return false;
    }
    public Num(int value){
        this.value=value;
    }
    //Public getter
    public int getValue(){
        return this.value;
    }
}
