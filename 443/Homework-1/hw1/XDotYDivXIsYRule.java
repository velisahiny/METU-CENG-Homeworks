package hw1;

public class XDotYDivXIsYRule implements Rule {
    private Var varX;
    private Var varY;
    private MathExpression premise;
    private MathExpression entails;
    @Override
    public MathExpression getPremise() {
        return premise;
    }

    @Override
    public MathExpression getEntails() {
        return entails;
    }
    //: constructs the premise and entailing expressions with the rule variables
    //    given as argument.
    public XDotYDivXIsYRule(Var x, Var y){
        this.varX=x;
        this.varY=y;
        this.premise= new Op("/",new Op("*", this.varX, this.varY) ,this.varX);
        this.entails= this.varY;
    }
    public Var getX(){
        return  this.varX;
    }
    public Var getY(){
       return this.varY;
    }
}
