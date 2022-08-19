import java.util.Iterator;

/**
 * A specialized SkipNavigableSet interface to implement only given operations in Part 2
 * @param <E> Type of Interface
 */
public interface ISkipNavigableSet<E> extends  Testable<E>{
    public boolean insert(E item);
    public E delete(E item);
    public Iterator<E> descendingIterator();
}
