
/*
*   This is a class to hold the heap and left and right children
*/
public class BigNode< E extends Comparable>  {
    public MyHeap<LittleNode<E>> heap;
    private int sizeLimit;
    public BigNode<E> left, right;
    private BigNode<E> parent;

/** sets the parent */
    public void setParent(BigNode<E> parent) {
        this.parent = parent;
    }                   //  θ(1)

    /** returns parent */
    public BigNode<E> getParent() {
        return parent;
    }                                      //  θ(1)


    /** constructs the instance with the given parameters (parent and depth) */
    public BigNode(int depth,BigNode<E> parent) {                                        //  θ(1)
        sizeLimit = 0;

        for (int i=0; i<=depth; i++)
            sizeLimit += Math.pow(2,i);
        this.parent = parent;

    }

    /** Constructs the instance with depth 2 */
    public BigNode(BigNode<E> parent) {                                                  //  θ(1)
        this(2,parent);

        heap = new MyHeap<LittleNode<E>>((o1, o2) -> o2.compareTo(o1));
    }


    /** returns if the heap is full or not */
    public boolean isFull(){
        return heap.size() == sizeLimit;
    }                              //  θ(1)
    /** returns if the heap is empty or not */
    public boolean isEmpty(){
        return heap.size() == 0;
    }                                     //  θ(1)

    /** returns the root value of the heap */
    public E getRootValue(){
        return heap.element().getElement();
    }                           //  θ(1)



    /** adds the given item to the heap */
    public int add(E item) throws Exception {                                                 //  O(log n)

        LittleNode<E> node = heap.search(new LittleNode<E>(item));            //  O(n)
        if(node != null)
            return node.increaseOccurence();             //  θ(1)


        if(isFull())
            throw new Exception("The heap is full. Can not be added new element.");
        else
        {
            node = new LittleNode<E>(item);                //  θ(1)
            heap.add(node);                                //  θ(1)
            return node.getOccurennce();                   //  O(log n)
        }
    }

    /** removes the given item from the heap */
    public int remove(E item) throws Exception {                                                        //  O(n)
        LittleNode<E> node1 = new LittleNode<>(item);                              //  θ(1)

        MyHeap.Iterator<LittleNode<E>> it = heap.iterator();                       //  θ(1)
        while (it.hasNext())                                                       //  O(n)
        {
            LittleNode<E> node2 = (LittleNode<E>) it.next();          //  θ(1)
            if(node1.equals(node2)) {                                 //  θ(1)
                if(node2.decreaseOccurence() == 0)
                {
                    it.remove();                                      //  θ(1)
                    return 0;                                         //  θ(1)
                }
                else
                    return  node2.getOccurennce();                    //  θ(1)
            }
        }
            return -1;
    }

    /** returns the size of the item given as argument */
    public int find(E item){                                                                  //  O(n)
        LittleNode<E> node = heap.search(new LittleNode<E>(item));              //  O(n)
        if(node != null)
            return node.getOccurennce();                   //  θ(1)
        else
            return -1;                                     //  θ(1)
    }

    /** compares root value with the given item */
    public int compareRoot(E item){
        return getRootValue().compareTo(item);
    }                    // θ(1)

    /** finds the mode of the heap */
    public LittleNode<E> find_mode(){                                                            //  O(n)
        int num = 0;
        LittleNode<E> node = null;

        MyHeap.Iterator<LittleNode<E>> it = heap.iterator();
        while (it.hasNext())
        {
            LittleNode<E> temp = (LittleNode<E>) it.next();        //  θ(1)
            int size = temp.getOccurennce();                       //  θ(1)
            if(num < size)
            {
                num = size;
                node = temp;                              //  θ(1)
            }
        }
        return node;
    }


    /** compares two BigNode by comparing roots */
    public int compareTo(BigNode<E> other) {                                               //  θ(1)
        return ((Comparable<E>) getRootValue()).compareTo(other.getRootValue());
    }

    /** Returns the string of the heap */
    @Override
    public String toString() {
        return heap.toString();
    }
}
