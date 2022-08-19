/**
 * extended BST class with rotate operations
 */
public class BSTWithRotate<E extends Comparable<E>> extends BST<E> {


    /**
     * Rotates tree to left from local root node
     */
    protected Node<E> rotateLeft(Node<E> localRoot){
        Node<E> temp = localRoot.right;
        localRoot.right = temp.left;
        temp.left = localRoot;
        localRoot =temp;

        return localRoot;

    }

    /**
     * Rotates tree to right from local root node
     */
    protected Node<E> rotateRight(Node<E> localRoot){
        Node<E> temp = localRoot.left;
        localRoot.left = temp.right;
        temp.right = localRoot;
        localRoot =temp;
        return localRoot;
    }
}