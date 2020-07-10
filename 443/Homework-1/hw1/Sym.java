package hw1;

/*Num and Sym are very similar. Although the homework forces you to implement them this way, can you think of
    a more "generic" solution? How would that affect the MathVisitor interface?*/

//Represents a mathematical variable (not a rule variable!). It should have the following:
public class Sym implements MathExpression {
    private String value;
    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(me instanceof Sym){
            return ((Sym) me).getValue().equals(value);
        }
        return false;
    }

    public Sym(String value){
        this.value=value;
    }
    // as public getter.
    public String getValue(){
        return this.value;
    }


}

