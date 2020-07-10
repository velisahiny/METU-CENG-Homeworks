package hw1;

import java.util.ArrayList;

public class PrintHTMLVisitor implements TextVisitor<String> {
    @Override
    public String visit(Document document) {

        ArrayList<DocElement> elements = document.getElements();
        StringBuffer stringBuffer=new StringBuffer();
        for(DocElement de : elements){
            stringBuffer.append(de.accept(this));
        }
        String str ="<html><head><title>"
                + document.getTitle()
                + "</title></head><body>"
                + stringBuffer.toString()
                + "</body></html>";
        return str;
    }

    @Override
    public String visit(EquationText equationText) {
        PrintMathMLVisitor printer = new PrintMathMLVisitor();
        MathExpression innerMath = equationText.getInnerMath();
        String strInner = innerMath.accept(printer);
        String str = "<math>"+ strInner + "</math>";
        return str;
    }
    @Override
    public String visit(Paragraph paragraph) {
        String str = "<p>" +paragraph.getText()+"</p>" ;
        return str;
    }
}
