package grt;

public class PrintMathMLVisitor2 implements MathVisitor<String> {

    private int mo_code;

    public PrintMathMLVisitor2(int mo_code) {
        this.mo_code = mo_code;
    }

    @Override
    public String visit(Num num) {
        return "<mrow><mn>"+((Integer)num.getValue()).toString()+"</mn></mrow>";
    }

    @Override
    public String visit(Op op) {
        switch(op.getOperand())
        {
            case "*":
                return "<mrow><mo>(</mo>"+op.getFirst().accept(this)+"<mo>&times;</mo>"+
                        op.getSecond().accept(this)+"<mo>)</mo></mrow>";
            case "+":
                return "<mrow><mo>(</mo>"+op.getFirst().accept(this)+"<mo>+</mo>"+
                        op.getSecond().accept(this)+"<mo>)</mo></mrow>";
            case "/":
                return "<mrow><mfrac>"+op.getFirst().accept(this)+op.getSecond().accept(this)+"</mfrac></mrow>";
            case "|-":
                if(mo_code == 0) {
              return "<mrow><mo>(</mo>"+op.getFirst().accept(this)+"<mo>&vdash;</mo></mrow>"+
                      op.getSecond().accept(this)+"<mo>)</mo>";
                }
                else {
                    return "<mrow><mo>(</mo>" + op.getFirst().accept(this) + "<mo>&vdash;</mo>" +
                            op.getSecond().accept(this) + "<mo>)</mo></mrow>";
                }
            default:
                return "<mrow><mo>(</mo>"+op.getFirst().accept(this)+op.getOperand()+
                        op.getSecond().accept(this)+"<mo>)</mo></mrow>";
        }
    }

    @Override
    public String visit(Sym sym) {
        return "<mrow><mi>"+sym.getValue()+"</mi></mrow>";
    }

    @Override
    public String visit(Var var) {
        if(var.getPreviousMatch() == null) {
            return "<mrow><msub><mi>V</mi><mn>"+((Integer)var.getId()).toString()+"</mn></msub></mrow>";
        }
        else {
            return "<mrow><msub><mi>V</mi><mn>"+((Integer)var.getId()).toString()+
                    "</mn></msub>"+
                    "<mo>[</mo>"+var.getPreviousMatch().accept(this)+"<mo>]</mo></mrow>";
        }
    }
}
