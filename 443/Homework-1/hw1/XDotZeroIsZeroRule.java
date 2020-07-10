package hw1;

public class XDotZeroIsZeroRule implements Rule{
    private MathExpression premise;
    private MathExpression entails;
    private Var varX;
    @Override
    public MathExpression getPremise() {
        return premise;
    }

    @Override
    public MathExpression getEntails() {
        return entails;
    }
    //: constructs the premise and entailing expressions with the rule variables given
    //    as argument.
    public XDotZeroIsZeroRule(Var x){
        this.varX=x;
        premise=new Op("*",this.varX,new Num(0));
        entails=new Num(0);
    }
   public Var getX(){
      return this.varX;
   }
}
