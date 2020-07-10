package hw1;
    /*Represents a rule variable. It contains the expression it previously matched, to check if that matches the next
    candidate expression. It should have the following:*/

public class Var implements MathExpression {
    private int id;
    private MathExpression previousMatch=null;
    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }
    /*it there has been no match for this, the match succeeds and it should be recorded. If there has been a previous match, returns the match result of
    this.getPreviousMatch() and me.*/
    @Override
    public boolean match(MathExpression me) {
        if(this.getPreviousMatch()==null ){
            this.setPreviousMatch(me);
            return true;
        }
        else{
            return this.getPreviousMatch().match(me);
        }
    }
    // the id is just for easy visual identification of the same Var instance.
    public Var(int id){
        this.id=id;
    }
    //public getter for the id.
    public int getId(){
        return this.id;
    }
    //set the recent successfully matched expression.
    public void setPreviousMatch(MathExpression me){
        this.previousMatch=me;
    }
    //get the recent successfully matched expression. If there has been no match yet, returns null.
    public MathExpression getPreviousMatch(){
        return this.previousMatch;
    }
}
