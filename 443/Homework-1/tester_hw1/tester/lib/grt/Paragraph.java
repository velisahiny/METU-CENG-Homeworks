package grt;

public class Paragraph implements DocElement {
    private String text;

    public Paragraph(String text) {
        this.text = text;
    }

    @Override
    public <T> T accept(TextVisitor<T> textVisitor) {
        return textVisitor.visit(this);
    }

    public String getText() {
        return text;
    }

}
