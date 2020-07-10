package hw1;
/*2.2.2 Paragraph class
Holds text. It should have the following:
*/
public class Paragraph implements  DocElement{
    private String text;
    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }

    public Paragraph(String text){
        this.text=text;
    }
    //public getter
    public String getText(){
        return this.text;
    }
}
