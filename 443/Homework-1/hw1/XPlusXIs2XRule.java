package hw1;

public class XPlusXIs2XRule implements Rule {
    private Var varX;
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
    //: constructs the premise and entailing expressions with the rule variable given as
    //    argument.
    public XPlusXIs2XRule(Var x){
        this.varX=x;
        premise=new Op("+",this.varX,this.varX);
        entails= new Op("*", new Num(2), varX);
    }
    public Var getX(){
        return this.varX;
    }
}
