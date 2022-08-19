/** This is a class to hold the elements and occurences(size) of it */
public class LittleNode<E extends Comparable> implements Comparable {
    private int size;
    private E element;

    /** Constructs the instance with the given element */
    public LittleNode(E element) {                                                     //  θ(1)
        this.element = element;
        size = 1;
    }

    /** Increases the occurence */
    public int increaseOccurence(){
        return ++size;
    }                                 //  θ(1)

    /** Decreases the occurence */
    public int decreaseOccurence(){
        return --size;
    }                                 //  θ(1)

    /** Returns if occurence is 0 or not */
    public boolean isEmpty(){
        return size == 0;
    }                                     //  θ(1)

    /** Returns the element */
    public E getElement(){
        return element;
    }                                           //  θ(1)

    /** Returns the occurence */
    public int getOccurennce() {
        return size;
    }                                         //  θ(1)

    /** Returns if the given object is equals to the instance */
    @Override
    public boolean equals(Object o) {                                                             //  θ(1)
        if( o != null && o instanceof LittleNode)
            return ((LittleNode<E>) o).element.equals(this.element);   // Let say θ(1)

        else
            return false;                              //  θ(1)
    }

    /** Compares with another instance */
    @Override
    public int compareTo(Object o) {
            return element.compareTo(((LittleNode<E>) o).element);                     //  Let say θ(1)
    }

    /** Returns the string of it */
    @Override
    public String toString() {                                                         //  θ(1)
        StringBuilder sb = new StringBuilder();
        sb.append("(");
        sb.append(element);
        sb.append(",");
        sb.append(size);
        sb.append(")");

        return sb.toString();
    }
}


