package hw1;
/*2.2.4 Document class
A collection of DocElements, with a title. It should have the following:
*/

import java.util.ArrayList;
public class Document implements DocElement {
    private String title;
    private ArrayList<DocElement> elements;
    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }
    //constructs a document with no elements, with title as title.
    public Document(String title){
        this.title=title;
        elements= new ArrayList<DocElement>();
    }
    //a getter of all the elements, in the order they were added.
    public ArrayList<DocElement> getElements(){
        return this.elements;
    }
    //the collection is reset to the elements inside arr, as if they were added in the order as they are in arr.
    public void setElements(ArrayList<DocElement> arr){
        this.elements=arr;
    }
    //adds de to the collection.
    public void add(DocElement de){
        this.elements.add(de);
    }
    //public setter for the title
    public void setTitle(String title){
        this.title=title;
    }
    //public getter for the title
    public String getTitle(){
        return this.title;
    }


}
