package grt;

public interface Rule {

    ClearVarsVisitor clearVarsVisitor = new ClearVarsVisitor();
    MathExpression getPremise();

    default boolean apply(MathExpression me)
    {
        clear();
        boolean result = getPremise().match(me);
        if(!result) clear();
        return result;
    }

    default void clear()
    {
        getPremise().accept(clearVarsVisitor);
    }

    MathExpression getEntails();

    default MathExpression entails(MathExpression me)
    {
        clear();
        apply(me);
        return getEntails();
    }

}
