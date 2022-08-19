
/** This is a class to hold all structure of BST Heap Tree */
public class BSTHeapTree<E extends Comparable<E>> {

    private BigNode<E> root;

    /** Constructor method to instantiate */
    public BSTHeapTree() {
        root = new BigNode<>(null);
    }                               //  θ(1)

    /** adds the given item */
    public int add(E item) throws Exception {                                              //  O(log m * log n)
        return add(root,item);
    }
    /** adds the item to the given root recursively */
    private int add(BigNode<E> root, E item) throws Exception {                            //  O(log m * log n)
        if(root.find(item) == 0 || root.find(item) == -1)
        {
            if(root.isFull()){
                if(root.compareRoot(item) > 0) {
                    if(root.left == null)
                        root.left = new BigNode<>(root);
                    return add(root.left, item);
                }
                else
                {
                    if(root.right == null)
                        root.right = new BigNode<>(root);
                    return add(root.right,item);
                }
            }
            else
                return root.add(item);                   //  O(log n)

        }
        else{
            return root.add(item);                       //  O(log n)
        }
    }



    /** removes the given item */
    public int remove(E item) throws Exception {                                    // O(n)
        return remove(root,item);
    }

    /** Removes the given item from the root recursively and deletes if the node is empty */
    private int remove(BigNode<E> root, E item) throws Exception {          // same algorithm with textbook O(n)
        if(root == null)
            throw new Exception("The given element is not found to remove");
        else {
            if(root.getRootValue().compareTo(item) >= 0){
                int remain = root.remove(item);
                if (remain == -1)
                    return remove(root.left, item);
                else if(root.isEmpty())        // if the root is empty
                {
                    if(root.left == null)
                    {
                        if(root.right != null)
                            makeParent(root.right);
                        else {
                            if (root.getParent() != null) {
                                if (root.getParent().left == root)
                                    root.getParent().left = null;
                                else
                                    root.getParent().right = null;
                            } else
                                this.root = new BigNode<>(null);
                        }
                    }
                    else if (root.right == null)
                        makeParent(root.left);
                    else{
                        if(root.left.right == null){
                            root.heap = root.left.heap;
                            root.left = root.left.left;
                            root.left.setParent(root);
                        }
                        else {
                            BigNode<E> largest = findLargestChild(root.left);
                            root.heap = largest.heap;
                            if(largest.getParent().right != null)
                                largest.getParent().right = null;
                            else
                                largest.getParent().left = null;
                        }
                    }
                    return remain;
                }
                else
                    return remain;
            }
            else
                return remove(root.right,item);
        }
    }

    /** returns largest child */
    private BigNode<E> findLargestChild(BigNode<E> root) {                                  // O(n)
        if(root.right != null)
            return findLargestChild(root.right);
        else
            return root;
    }

    /** makes parent the given child */
    private void makeParent(BigNode<E> root) {                                              //  θ(1)
        if(root.getParent() != null)
        {
            root.getParent().heap = root.heap;
            root.getParent().right = root.right;
            root.getParent().left = root.left;
        }
        else
            this.root = root;
            this.root.right = root.right;
            this.root.left = root.left;
    }

    /** Finds the given item as argument */
    public int find(E item) throws Exception {              //  O(a)
        return find(root,item);
    }

    /** Finds the given item in the root recursively*/
    private int find(BigNode<E> root, E item) throws Exception {            // let say all elements is a -> O(a)
        if(root == null || root.isEmpty())
            throw new Exception("The given element is not found");
        else {
            if(root.getRootValue().compareTo(item) >= 0){
                int remain = root.find(item);
                if (remain == -1)
                    return find(root.left, item);
                else
                    return remain;
            }
            else
                return find(root.right,item);
        }
    }

    /** Finds the mode  */
    public E find_mode(){
        return find_mode(root).getElement();
    }           // O(a)

    /** Finds the mode in the given root recursively */
    private LittleNode<E> find_mode(BigNode<E> root){                       // let say all elements is a -> O(a)

        LittleNode<E> mode = root.heap.element();              //  θ(1)
        LittleNode<E> temp = null;                             //  θ(1)

        if(root.heap != null )
        {
            temp = root.find_mode();
            if(temp.getOccurennce() > mode.getOccurennce())
                mode = temp;
        }
        if(root.left != null )
        {
            temp = find_mode(root.left);
            if(temp.getOccurennce() > mode.getOccurennce())
                mode = temp;
        }
        if(root.right != null) {
            temp = find_mode(root.right);
            if(temp.getOccurennce() > mode.getOccurennce())
                mode = temp;
        }
        return mode;
    }






    /** Returns the string of the all elements */
    @Override
    public String toString() {
       return toString(root);
    }

    /** Returns the string of the all elements in the given root */
    private String toString(BigNode<E> root){           // let say all elements is a -> O(a)

        StringBuilder sb = new StringBuilder();
        if(root.left != null)
            sb.append(toString(root.left) + "  ");
        sb.append(root + "  ");
        if(root.right != null)
            sb.append(toString(root.right) + "  ");

        return sb.toString();

    }


    /** Tests for the class */
    public static void main(String[] args){

        BSTHeapTree<Integer> bst = new BSTHeapTree<>();
        try {
            bst.add(12);
            bst.add(24);
            bst.add(12);
            System.out.println(bst);

            bst.remove(12);
            bst.remove(12);
            System.out.println(bst);
            bst.remove(24);
            System.out.println(bst);


            System.out.println( bst.find(10) );


        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            bst.add(34);
            bst.add(34);
            bst.add(13);
            bst.add(13);
            bst.add(13);
            System.out.println( bst.find(34) );
            System.out.println( bst.find_mode() );

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }






    }

}
