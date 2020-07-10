package hw1;

public interface Rule {

    //: clears all rule variables in the premise and entailing expressions. You can implement this as
    //a default method. How?
    default void clear(){
        ClearVarsVisitor cvv= new ClearVarsVisitor();
        getPremise().accept(cvv);
        getEntails().accept(cvv);
    }

    // clears all rule variables in the premise and entailing expressions, and then attempts matching me to the premise.
    // If the match fails, the premise and the entailing expression
    //should stay clear. If the match succeeds, the rule variables in the premise and the entailing expression
    //should be updated to show what was matched. Returns the result of the matching process. You can safely
    //assume that me will not contain any Vars, although if your implementation is good, then your method
    //will not have a problem with that as well. You can implement this as a default method. How?
    default boolean apply(MathExpression me){
        clear();
        if(getPremise().match(me)){
            return true;
        }else{
            clear();
            return false;
        }
    }

    //: returns the premise expression.
    MathExpression getPremise();
    //: returns the entailing expression.
    MathExpression getEntails();
    //: calls apply(me) and then returns getEntails(). You
    //    can implement this as a default method - obviously.
    default MathExpression entails(MathExpression me){
        apply(me);
        return getEntails();
    }
}
