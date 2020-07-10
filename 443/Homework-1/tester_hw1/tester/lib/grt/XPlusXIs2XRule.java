package grt;

public class XPlusXIs2XRule implements Rule {

    private static Num two = new Num(2);

    private Var x;
    private MathExpression x_plus_x;
    private MathExpression two_x;

    public XPlusXIs2XRule(Var x) {
        this.x = x;
        x_plus_x = new Op("+",x,x);
        two_x = new Op("*",two,x);
    }


    @Override
    public MathExpression getPremise() {
        return x_plus_x;
    }

    @Override
    public MathExpression getEntails() {
        return two_x;
    }

    public Var getX() {
        return x;
    }
}
