/**
 * The inteface for the class that has id
 */
public interface Identifiable extends Comparable{

    /**
     * returns the id of the object
     * @return the id
     */
    public Integer getId();

    @Override
    int compareTo(Object o);
}
