package grt;

public class PrintHTMLVisitor implements TextVisitor<String> {

    private static PrintMathMLVisitor mathMLVisitor = new PrintMathMLVisitor();

    @Override
    public String visit(Document document) {
        StringBuilder paragraphs = new StringBuilder();
        for (DocElement e:document.getElements()) {
            paragraphs.append(e.accept(this));
        }
        //return "<html><head><title>"+document.getTitle()+"</title></head><body>"+paragraphs.toString()+"</body><html>";
        return "<html><head><title>"+document.getTitle()+"</title></head><body>"+paragraphs.toString()+"</body></html>";
    }

    @Override
    public String visit(Paragraph paragraph) {
        return "<p>"+ paragraph.getText()+"</p>";
    }

    @Override
    public String visit(EquationText eq) {
        //return "<p><math>"+eq.getInnerMath().accept(mathMLVisitor)+"</math></p>";
        return "<math>"+eq.getInnerMath().accept(mathMLVisitor)+"</math>";
    }
}
