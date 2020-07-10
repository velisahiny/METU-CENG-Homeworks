package grt;

public interface DocElement {
    <T> T accept(TextVisitor<T> textVisitor);
}
