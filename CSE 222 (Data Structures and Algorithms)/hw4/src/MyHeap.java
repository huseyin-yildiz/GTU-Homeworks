import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

/** This is a class Which customized implementation of Heap structure */
public class MyHeap<E extends Comparable> {
    private PriorityQueue<E> data;

    /** Constructs the heap with the given comparator */
    public MyHeap(Comparator<E> comparator) {
        this.data = new PriorityQueue<E>(comparator);
    }           //  θ(1)

    /** Constructs the heap */
    public MyHeap() {
        this.data = new PriorityQueue<E>();
    }                                               //  θ(1)

    /** Adds the element to the heap */
    public boolean add(E element){                                                                      //  O(log n)
        LittleNode<E> node = new LittleNode<E>(element);    //  θ(1)
        return data.add(element);                           //  O(log n)
    }

    /** Removes the first element */
    public E remove(){
        return data.remove();
    }                                                       //  O(log n)

    /** Seaeches the given element in the heap */
    public E search(E element){                                                                       // O(n)
        Iterator it = iterator();             //  θ(1)
        while (it.hasNext()) {                  // O(n)
            E item = (E) it.next();
            if (item.equals(element))
                return item;
        }
        return null;
    }

    /** Merges the heap with the given element */
    public boolean merge(MyHeap myHeap){
        return data.addAll(myHeap.data);
    }                          // O(mlogn)

    /** Takes first element without removing */
    public E element(){ return data.element(); }                                                    //  θ(1)

    /** Returns the size of the heap */
    public int size(){ return data.size(); }                                                        //  θ(1)

    /** Removes the i'th largest element from the heap */
    public boolean remove(int index){                                                               //  O(n)
        int removedSize = data.size() - index;  //  θ(1)
        if(data.size() < index || index < 1)    //  θ(1)
            return false;
        else {
            Iterator it = iterator();           //  θ(1)
          //  int counter = 0;
//
            List<E> temp = new ArrayList<>();         //  θ(1)

            while (data.size() != index)                 //  θ(index)
                temp.add(data.remove());
            data.remove();                       //  O(n)
            data.addAll(temp);                   //  O(index)
            return true;

        }
    }

    /** This is a extended iterator interface for the heap */
    public interface Iterator<E> extends java.util.Iterator {

        /*
         *  sets the last element returned
         */
        public boolean set(E element);
    }

    /** Returns an iterator for traversing the heap  */
    public Iterator<E> iterator(){                                               //  θ(1)
        return new Iterator<E>() {

            java.util.Iterator it = data.iterator();
            E lastItem;
            int index = -1;

            /*
             *  sets the last returned element ( !! After the setting iterator goes to the same index because the index of setted item can be changed !! )
             */
            @Override
            public boolean set(E element) {                                     //  O(n)
                boolean flag = false;
                if(lastItem != null) {
                    it.remove();                               //  θ(1)
                    flag = data.add(element);                  //  O(log n)
                    it = data.iterator();                      //  θ(1)
                    int i = -1;                                //  θ(1)
                    while (it.hasNext())                       //  O(n)
                    {
                        it.next();                   //  θ(1)
                        i++;                         //  θ(1)
                        if(i == index)               //  θ(1)
                            break;

                    }
                }
                return flag;
            }

            /** Returns if there is next element or not */
            @Override
            public boolean hasNext() {
                return it.hasNext();
            }                      //  θ(1)

            /** Returns the next element */
            @Override
            public E next() {                                                      //  θ(1)
                lastItem = (E) it.next();
                index++;
                return lastItem;
            }

            /** Removes the last element returned */
            @Override
            public void remove() {
                it.remove();
            }                            //  θ(1)
        };
    }

    /** Returns the string of the heap */
    @Override
    public String toString() {
        return data.toString();
    }
}