import java.util.Arrays;
import java.util.Random;

/**
 * The class for the SkipList
 * @param <E>
 */
public class SkipList<E extends Comparable<E>> implements Testable<E>{

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
    /** The head node is a dummy node, it contains no data */
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
     * Inserts item where it belongs in the tree.
     * @param item The item to be inserted
     * @return True if item is inserted; false if it isn't (already in tree).
     */
    public boolean add(E item) {
        SLNode<E>[] update = search(item);

        // check if item is already in list
        if (update[0].links[0] != null && update[0].links[0].data.compareTo(item) == 0) {
            return false;
        }

        size++;
        // increase the height if needed
        if (size > maxCap) {
            maxLevel++;
            maxCap = computeMaxCap(maxLevel);
            head.links = Arrays.copyOf(head.links, maxLevel);
            update = Arrays.copyOf(update, maxLevel);
            update[maxLevel - 1] = head;
        }
        // Create new node for the item
        SLNode<E> itemNode = new SLNode<E>(logRandom(), item);

        // Insert the node into the list
        for (int i = 0; i < itemNode.links.length; i++) {
            // Set the new node's references
            itemNode.links[i] = update[i].links[i];
            // Set the old references to the new node
            update[i].links[i] = itemNode;
        }
        return true;
    }

    /**
     * Determine if an item is in the tree
     * @param target Item being sought in tree
     * @return true If the item is in the tree, false otherwise
     */
    public boolean contains(E target) {
        return find(target) != null;
    }


    /**
     * Find and delete target from tree.
     * @param target The item to delete.
     * @return The item if it is present, null otherwise
     */
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
    /**
     * Removes target from tree.
     * @post target is not in the tree
     * @param target Item to be removed
     * @return true if the object was in the tree, false otherwise
     */
    public boolean remove(E target) {
        return delete(target) != null;
    }

    /** Remove all data from the tree */
    public void clear() {
        for (int i = 0; i < maxLevel; i++) {
            head.links[i] = null;
        }
        size = 0;
    }


    /**
     * Returns a string representation of the data in the skip list
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