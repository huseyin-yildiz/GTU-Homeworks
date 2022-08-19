package Containers;

import java.util.Arrays;
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.Iterator;

public class KWArrayList<E> extends AbstractList<E> implements IContainer<E>
{

    /** The default initial capacity */
    private static final int INITIAL_CAPACITY = 10;
    /** The underlying data array */
    private E[] theData;
    /** The current size */
    private int size = 0;
    /** The current capacity */
    private int capacity = 0;

    /**
     * Construct an empty KWArrayList with the default
     * initial capacity
     */
    public KWArrayList() {										// θ(1)
        capacity = INITIAL_CAPACITY;
        theData = (E[]) new Object[capacity];
    }



    /**
     * Add an entry to the data inserting it before the
     * item at the specified index.
     * @param index - The index of the time that the new
     *        value it to be inserted in front of.
     * @param theValue - The value to be inserted
     * @throws ArrayIndexOUtOfBoundsException if index is
     *         less than zero or greater than size
     */
    public boolean add(E anEntry) {								// amortised θ(1)
        if (size == capacity) {
            reallocate();
        }
        theData[size] = anEntry;
        size++;
        return true;
    }

    /**
     * Get a value in the array based on its index.
     * @param index - The index of the item desired
     * @return The contents of the array at that index
     * @throws ArrayIndexOutOfBoundsException - if the index
     *         is negative or if it is greater than or equal to the
     *         current size
     */
    public E get(int index) {									// θ(1)
        if (index < 0 || index >= size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        return theData[index];
    }

    /**
     * Set the value in the array based on its index.
     * @param index - The index of the item desired
     * @param newValue - The new value to store at this position
     * @return The old value at this position
     * @throws ArrayIndexOutOfBoundsException - if the index
     *         is negative or if it is greater than or equal to the
     *         current size
     */
    public E set(int index, E newValue) {							// θ(1)
        if (index < 0 || index >= size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        E oldValue = theData[index];
        theData[index] = newValue;
        return oldValue;
    }

    /**
     * Remove an entry based on its index
     * @param index - The index of the entry to be removed
     * @return The value removed
     * @throws ArrayIndexOutOfBoundsException - if the index
     *         is negative or if it is greater than or equal to the
     *         current size
     */
    public E remove(int index) {									// Tw(n)= θ(n) Tb(1)= θ(1) -> O(n)
        if (index < 0 || index >= size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        E returnValue = theData[index];
        for (int i = index + 1; i < size; i++) {
            theData[i - 1] = theData[i];
        }
        size--;
        return returnValue;
    }

    /**
     * Allocate a new array to hold the directory
     */
    private void reallocate() {								// θ(n)
        capacity = 2 * capacity;
        theData = Arrays.copyOf(theData, capacity);
    }

    /**
     * Get the current size of the array
     * @return The current size of the array
     */
    public int size() {									// θ(1)
        return size;
    }


    public KWArrayList(int capacity) {					// θ(n)
        theData = (E[]) new Object[capacity];
    }


	/** Returns a string representation of this collection. */
	@Override
	public String toString() 							// θ(n^2)
	{
		return toString(" -- ");
	}
	
	public String toString(String interString) {			// θ(n^2)
		String text = new String();
		Iterator<E> it = iterator();
		while(it.hasNext()) 								// if we use stringBuilder it would be // θ(n)
			text += it.next() + interString;
		
		return text;
	}



	@Override
	public E find(E e) throws Exception {					// θ(n)	
		Iterator<E> it = iterator();
		while(it.hasNext()) 
		{
			E element = it.next(); 
			if(element.equals(e))
				return element;
		}
		throw new Exception("The given element not included");
	}



  

    
}
