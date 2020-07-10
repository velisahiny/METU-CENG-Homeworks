package grt;

public class XDotZeroIsZeroRule implements Rule {

    private static Num zero = new Num(0);

    private MathExpression capturingElement;

    public Var getX() {
        return x;
    }

    private Var x;

    public XDotZeroIsZeroRule(Var x) {
        this.x = x;
        capturingElement = new Op("*",x,zero);
    }


    @Override
    public MathExpression getPremise() {
        return capturingElement;
    }

    @Override
    public MathExpression getEntails() {
        return zero;
    }
}
