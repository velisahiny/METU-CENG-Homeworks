package grt;

public class PrintHTMLVisitor2 implements TextVisitor<String> {

    private PrintMathMLVisitor2 mathMLVisitor;
    private int mocode;
    private int htmlcode;
    private int mathcode;

    public PrintHTMLVisitor2(int mocode, int htmlcode, int mathcode) {
        this.mocode = mocode;
        this.htmlcode = htmlcode;
        this.mathcode = mathcode;
        mathMLVisitor = new PrintMathMLVisitor2(mocode);
    }

    @Override
    public String visit(Document document) {
        StringBuilder paragraphs = new StringBuilder();
        for (DocElement e : document.getElements()) {
            paragraphs.append(e.accept(this));
        }
        if (htmlcode == 0) {
            return "<html><head><title>" + document.getTitle() + "</title></head><body>" + paragraphs.toString() + "</body><html>";
        } else {
            return "<html><head><title>" + document.getTitle() + "</title></head><body>" + paragraphs.toString() + "</body></html>";
        }
    }

    @Override
    public String visit(Paragraph paragraph) {
        return "<p>"+ paragraph.getText()+"</p>";
    }

    @Override
    public String visit(EquationText eq) {
        if(mathcode == 0) {
            return "<p><math>"+eq.getInnerMath().accept(mathMLVisitor)+"</math></p>";
        }
        else {
            return "<math>" + eq.getInnerMath().accept(mathMLVisitor) + "</math>";
        }
    }
}
