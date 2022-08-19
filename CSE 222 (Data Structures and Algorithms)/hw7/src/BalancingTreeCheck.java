/**
 * The class to determine if a binary search tree is avl or is red-black tree for part 2
 */
public class BalancingTreeCheck {

    /**
     * Checks if the given Binary Search Tree is an AVL or not
     * @param bst Binary Search Tree
     * @return is the given bst AVL
     */
    public static boolean isAVL(BST bst){
        return isAVL(bst.root);
    }

    /**
     * The helper recursive function of the public isAVL method
     * @param root the root of the binary search tree
     * @return is the given bst AVL
     */
    private static boolean isAVL( BinaryTree.Node root ){
        if(root == null)
            return true;

        int leftSize = calculateHeight(root.left);
        int rightSize = calculateHeight(root.right);
        if(rightSize-leftSize <=1 && rightSize-leftSize >=-1)
            return isAVL(root.left) && isAVL(root.right);
        else
            return false;
    }

    /**
     * The helper function of the isAVL method to calculate
     * height of a node from the leaf
     * @param root the root to calculate height
     * @return height
     */
    private static int calculateHeight(BinaryTree.Node root){
        if(root==null)
            return 0;
        int leftSize = calculateHeight(root.left);
        int rightSize = calculateHeight(root.right);
        int max = Math.max(leftSize, rightSize);
        return max+1;
    }

    /**
     * Checks if the given Binary Search Tree is an RedBlack or not
     * @param bst Binary Search Tree
     * @return is the given bst RedBlack
     */
    public static boolean isRedBlack(BST bst){
        if(((RedBlackTree.RedBlackNode) bst.root).isRed())
            return false;
        int sizeToLeaf = isSameRootToLeaf(((RedBlackTree.RedBlackNode) bst.root));
        return !isRedConsecutive(((RedBlackTree.RedBlackNode) bst.root)) && sizeToLeaf!=-1;
    }

    /**
     * The helper method of the isRedBlack method to find
     * if is there any consecutive red node
     * @param root The starting node to process
     * @return are there any red consecutive or not
     */
    private static boolean isRedConsecutive(RedBlackTree.RedBlackNode root){

        if(root == null)
            return false;
        if(root.isRed() && root.left!=null && (((RedBlackTree.RedBlackNode) root.left).isRed()))
            return true;
        if(root.isRed() && root.right!=null && (((RedBlackTree.RedBlackNode) root.right).isRed()))
            return true;
        if( isRedConsecutive(((RedBlackTree.RedBlackNode) root.left)))
            return true;

        return isRedConsecutive(((RedBlackTree.RedBlackNode) root.right));
    }


    /**
     * The helper method of isRedConsecutive method that checks if size of black
     * nodes on the paths from the root to the leaves are same or not recursively
     * @param root starting root
     * @return if the tree is red-black returns the size
     * of black nodes either it returns -1
     */
    private static int isSameRootToLeaf(RedBlackTree.RedBlackNode root){
        int isBlack=1;
        if(root == null)
            return 1;
        if(root.isRed())
           isBlack=0;

        int left = isSameRootToLeaf(((RedBlackTree.RedBlackNode) root.left));
        int right = isSameRootToLeaf(((RedBlackTree.RedBlackNode) root.right));

        if(left == -1 || right == -1 || left!=right)
            return -1;
        return isBlack+left;
    }

}
