package grt;

import java.util.ArrayList;

public class Document implements DocElement {
    private String title;
    private ArrayList<DocElement> elements;

    public Document(String title) {
        this.title = title;
        elements = new ArrayList<>();
    }

    @Override
    public <T> T accept(TextVisitor<T> textVisitor) {
        return textVisitor.visit(this);
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public ArrayList<DocElement> getElements() {
        return elements;
    }

    public void setElements(ArrayList<DocElement> elements) {
        this.elements = elements;
    }

    public void add(DocElement docElement) {
        elements.add(docElement);
    }
}
