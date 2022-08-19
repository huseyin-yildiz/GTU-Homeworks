/**
 * The class for TwoThree Tree that made used with B-Tree
 * which is generalized version of this class
 * @param <E> The type of the TwoThree Tree
 */
public class TwoThreeTree<E extends Comparable<E>> extends BTree<E>{

    /**
     * Constructs a 2-3 tree
     *
     */
    public TwoThreeTree() {
        super(3);
    }
}
