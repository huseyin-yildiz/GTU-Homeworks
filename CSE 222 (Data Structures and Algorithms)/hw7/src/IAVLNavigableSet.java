import java.util.Iterator;

/**
 * A specialized Navigable Set interface to implement only given operations in Part 2
 * @param <E> Type of Interface
 */
public interface IAVLNavigableSet<E> extends Testable<E>{
    public boolean insert(E item);
    public Iterator<E> iterator();
    public IAVLNavigableSet<E> headSet(E toElement);
    public IAVLNavigableSet<E> tailSet(E toElement);

}
