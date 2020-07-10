package grt;

public class EquationText implements DocElement {
    private MathExpression innerMath;

    public EquationText(MathExpression innerMath) {
        this.innerMath = innerMath;
    }

    public MathExpression getInnerMath() {
        return innerMath;
    }
    @Override
    public <T> T accept(TextVisitor<T> textVisitor) {
        return textVisitor.visit(this);
    }
}
