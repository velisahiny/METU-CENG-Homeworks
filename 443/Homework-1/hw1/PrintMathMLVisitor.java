package hw1;
/*2.3.4 PrintMathMLVisitor implements MathVisitor<String>
Let visitor be of this type. Let me be a MathExpression. Calling me.accept(visitor) should return the
MathML string of the expression. Refer to Table 1 for treating the types:*/
public class PrintMathMLVisitor implements MathVisitor<String> {
    @Override
    public String visit(Op op) {
        String str;
        String firstString=null;
        String secondString=null;
        MathExpression first = op.getFirst();
        MathExpression second=op.getSecond();
        firstString=first.accept(this);
        secondString=second.accept(this);
        String operand= op.getOperand();
        if(operand!="/"){
            if(operand=="*"){
                operand="&times;";
            }else if(operand =="|-"){
                operand="&vdash;";
            }
            str="<mrow><mo>(</mo>"+ firstString +"<mo>"+ operand + "</mo>" +secondString+ "<mo>)</mo></mrow>";
        }
        else{
            str="<mrow><mfrac>"+ firstString + secondString + "</mfrac></mrow>";
        }
        return str;
    }

    @Override
    public String visit(Num num) {
        String str = "<mrow><mn>"+ num.getValue() +"</mn></mrow>";
        return str;
    }

    @Override
    public String visit(Sym sym) {
        String str = "<mrow><mi>"+ sym.getValue() +"</mi></mrow>";
        return str;
    }

    @Override
    public String visit(Var var) {
        String str;
        MathExpression prev=var.getPreviousMatch();
        if(prev==null){
            str="<mrow><msub><mi>V</mi><mn>"+ var.getId()+ "</mn></msub></mrow>";
        }else {
            String strPrev = prev.accept(this);
            str="<mrow><msub><mi>V</mi><mn>"+ var.getId()+ "</mn></msub><mo>[</mo>"+strPrev+"<mo>]</mo></mrow>";
        }
        return str;
    }
}
