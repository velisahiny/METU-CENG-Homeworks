package grt;

public interface TextVisitor<T> {
    T visit(Document document);
    T visit(Paragraph paragraph);
    T visit(EquationText eq);
}
