import java.util.*;

/**
 * The class for Navigable Skip-List
 * @param <E> The type of the class
 */
public class NavigableSkipList<E extends Comparable<E>> implements ISkipNavigableSet<E> {

    @Override
    public boolean add(E item) {
        return insert(item);
    }

    /** Static class to contain the data and the links */
    static class SLNode<E> {

        SLNode<E>[] links;
        E data;

        /** Create a node of level n */
        SLNode(int n, E data) {
            links = (SLNode<E>[]) new SLNode[n];
            this.data = data;
        }
    }
    /** Maximum level */
    int maxLevel = 2;
    /** Nominal maximum capacity */
    int maxCap = computeMaxCap(maxLevel);
    /** Natural Log of 2 */
    static final double LOG2 = Math.log(2.0);
    /** A random number generator */
    final static Random rand = new Random();
    /** The current size of the skipList */
    int size;

    /**
     * Method to compute the maximum capacity, given the maximum
     * level. It computes Math.pow(2, maxLevel) - 1, using shift.
     * @return Math.pow(2, maxLevel+1) - 1;
     */
    private static int computeMaxCap(int maxLevel) {
        return ~(~0 << maxLevel);
    }

    /**
     * Method to generate a logarithmic distributed integer between
     * 1 and maxLevel.  I.E. half of the values returned are 1, 1/4
     * are 2, 1/8 3, 1/16 4, etc.
     * @return a random logarithmic distributed int between 1 and maxLevel
     */
    private int logRandom() {
        int r = rand.nextInt(maxCap);
        int k = (int) (Math.log(r + 1) / LOG2);
        if (k > maxLevel - 1) {
            k = maxLevel - 1;
        }
        return maxLevel - k;
    }
    /** The head node contains no data */
    SLNode<E> head = new SLNode<E>(maxLevel, null);


    /**
     * Search for an item in the list
     * @param item The item being sought
     * @return A SLNode array which references the nodes
     *         preceeding the sought item at each level.
     */
    private SLNode<E>[] search(E item) {
        SLNode<E>[] result = (SLNode<E>[]) new SLNode[maxLevel];
        SLNode<E> current = head;
        for (int i = current.links.length - 1; i >= 0; i--) {
            while (current.links[i] != null && current.links[i].data.compareTo(item) < 0) {
                current = current.links[i];
            }
            result[i] = current;
        }
        return result;
    }

    /**
     * Find an object in the skip list
     * @param target The item being sought
     * @return A reference to the object in the skip list that compares
     *         equal as determined by compareTo to the target. If not
     *         found null is returned.
     */

    public E find(E target) {
        SLNode<E>[] update = search(target);
        if (update[0].links[0] != null && update[0].links[0].data.compareTo(target) == 0) {
            return update[0].links[0].data;
        } else {
            return null;
        }
    }


    /**
     * Inserts item where it belongs in the SkipList.
     * @param item The item to be inserted
     * @return True if item is inserted; false if it isn't (already in SkipList).
     */

    public boolean insert(E item) {
        SLNode<E>[] update = search(item);

        if (update[0].links[0] != null && update[0].links[0].data.compareTo(item) == 0) {
            return false;
        }

        size++;
        if (size > maxCap) {
            maxLevel++;
            maxCap = computeMaxCap(maxLevel);
            head.links = Arrays.copyOf(head.links, maxLevel);
            update = Arrays.copyOf(update, maxLevel);
            update[maxLevel - 1] = head;
        }

        SLNode<E> itemNode = new SLNode<E>(logRandom(), item);


        for (int i = 0; i < itemNode.links.length; i++) {
            itemNode.links[i] = update[i].links[i];
            update[i].links[i] = itemNode;
        }
        return true;
    }

    /**
     * Determine if an item is in the SkipList
     * @param target Item being sought in SkipList
     * @return true If the item is in the SkipList, false otherwise
     */

    public boolean contains(E target) {
        return find(target) != null;
    }




    /**
     * Find and delete target from SkipList.
     * @param target The item to SkipList.
     * @return The item if it is present, null otherwise
     */

    @Override
    public E delete(E target) {

        if (!contains(target)) {
            return null;
        }

        SLNode<E> targetNode = head;
        SLNode<E>[] update = (SLNode<E>[]) new SLNode[maxLevel];


        for (int i = targetNode.links.length - 1; i >= 0; i--) {
            while (targetNode.links[i] != null && targetNode.links[i].data.compareTo(target) < 0) {
                targetNode = targetNode.links[i];
            }
            update[i] = targetNode;
        }
        targetNode = targetNode.links[0];

        for (int i = 0; i < update.length; i++) {
            if (update[i].links[i] != targetNode) {
                break;
            }
            update[i].links[i] = targetNode.links[i];
        }
        size--;

        return target;
    }

    public class SLIterator<T> implements Iterator<T>{

        private Stack<T> s;
        private T lastItem;

        public SLIterator(){
            s = new Stack<>();
            SLNode<T> current = (SLNode<T>) head.links[0];
            while ( current!= null ){
                s.add(current.data);
                current = current.links[0];
            }

        }

        @Override
        public boolean hasNext() {
            return (!s.empty());
        }

        @Override
        public T next() {
            if(! hasNext())
                throw new NoSuchElementException();
            lastItem = s.pop();
            return lastItem;
        }

        public void remove(){
            delete((E) lastItem);
        }
    }


    @Override
    public Iterator<E> descendingIterator() {
        return new SLIterator<>();
    }



    /**
     * Returns a string representation of the data in the SkipList
     * @return The string representation
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        SLNode<E> x = head.links[0];
        while (x != null) {
            sb.append(x.data);
            x = x.links[0];
            if (x != null) {
                sb.append(", ");
            }
        }
        return sb.toString();
    }


}
