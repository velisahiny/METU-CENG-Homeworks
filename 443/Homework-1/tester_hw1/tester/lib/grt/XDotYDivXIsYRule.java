package grt;

public class XDotYDivXIsYRule implements Rule{

    public Var getX() {
        return x;
    }

    public Var getY() {
        return y;
    }

    private Var x;
    private Var y;
    private MathExpression x_dot_y_div_x;

    public XDotYDivXIsYRule(Var x, Var y) {
        this.x = x;
        this.y = y;
        x_dot_y_div_x = new Op("/",new Op("*",x,y),x);
    }


    @Override
    public MathExpression getPremise() {
        return x_dot_y_div_x;
    }

    @Override
    public MathExpression getEntails() {
        return y;
    }
}
