package Containers;

import java.util.AbstractSequentialList;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * Class KWLinkedList implements a double linked list and
 * a ListIterator.
 * @author Koffman & Wolfgang
 **/
public class KWLinkedList<E> extends AbstractSequentialList<E> implements IContainer<E> {
    /** A reference to the head of the list. */
    public Node<E> head = null;
    /** A reference to the end of the list. */
    public Node<E> tail = null;
    /** The size of the list. */
    public int size = 0;

    /**
     * Insert an object at the beginning of the list.
     * @param item - the item to be added
     */
    public void addFirst(E item) {											// θ(1)
       Node obj = new Node(item);
       if(head != null)
       {
         obj.next = head;
         head.prev = obj;
         head = obj;
       } else {
         head = obj;
         tail = obj;
       }
       size++;
    }

    /**
     * Insert an object at the end of the list.
     * @param item - the item to be added
     */
    public void addLast(E i) {												// θ(1)
      Node item = new Node(i);
      if(tail != null) {
         item.prev = tail;
         tail.next = item;
         tail = item;
      } else {
         head = item;
         tail = item;
      }
      size++;
    }

    /**
     * Get the first element in the list.
     * @return The first element in the list.
     */
    public E getFirst() {										// θ(1)
       return head.data;
    }

    /**
     * Get the last element in the list.
     * @return The last element in the list.
     */
    public E getLast() {										// θ(1)
      return tail.data;
    }
    
    /**
     * Return an Iterator to the list
     * @return an Itertor to the list
     */
    public Iterator<E> iterator() {								// θ(1)
       KWListIter iterator = new KWListIter(0);	
       return iterator;
    }

    /**
     * Return a ListIterator to the list
     * @return a ListItertor to the list
     */
    public ListIterator<E> listIterator() {						// θ(1)
       KWListIter iterator = new KWListIter(0);
       return iterator;
    }

    /** Return a ListIterator that begins at index
     * @param index - The position the iteration is to begin
     * @return a ListIterator that begins at index
     */
    public ListIterator<E> listIterator(int index) {				// θ(n)
       KWListIter iterator = new KWListIter(index);
       return iterator;
    }

    /**
     * Return a ListIterator that begins at the same
     * place as an existing ListIterator
     * @param iter - The other ListIterator
     * @return a ListIterator that is a copy of iter
    */
    public ListIterator <E> listIterator(ListIterator <E> iter) {				// θ(1)
       KWListIter iterator = new KWListIter((KWListIter)iter);
       return iterator;
    }
    /*</exercise>*/
    /**
     * Add an item at the specified index.
     * @param index The index at which the object is to be
     *        inserted
     * @param obj The object to be inserted
     * @throws IndexOutOfBoundsException if the index is out
     *         of range (i < 0 || i > size())
     */
    @Override
    public void add(int index, E obj) {											// O(n)
        listIterator(index).add(obj);
    }

    /**
     * Get the element at position index.
     * @param index Position of item to be retrieved
     * @return The item at index
     */
    @Override
    public E get(int index) {													// O(n)
        return listIterator(index).next();
    }

    /**
     * Return the size of the list
     * @return the size of the list
     */
    @Override
    public int size() {															// θ(1)
        return size;
    }

    // Inner Classes
    /** 
     * A Node is the building block for a double-linked list.
     */
    private static class Node<E> {

        /** The data value. */
        public E data;
        /** The link to the next node. */
        public Node<E> next = null;
        /** The link to the previous node. */
        public Node<E> prev = null;

        /**
         * Construct a node with the given data value.
         * @param dataItem The data value
         */
        private Node(E dataItem) {
            data = dataItem;
        }
        
        public String getData() {										// θ(1)
            if(data == null)
               return "null";
            else 
               return (String)data;
        }
    } //end class Node

    /** Inner class to implement the ListIterator interface. */
    private class KWListIter implements ListIterator<E> {

        /** A reference to the next item. */
        private Node<E> nextItem;
        /** A reference to the last item returned. */
        private Node<E> lastItemReturned;
        /** The index of the current item. */
        private int index = 0;

        /**
         * Construct a KWListIter that will reference the ith item.
         * @param i The index of the item to be referenced
         */
        public KWListIter(int i) {										// O(n)
            // Validate i parameter.
            if (i < 0 || i > size) {
                throw new IndexOutOfBoundsException(
                        "Invalid index " + i);
            }
            lastItemReturned = null; // No item returned yet.
            // Special case of last item.
            if (i == size) {
                index = size;
                nextItem = null;
            } else { // Start at the beginning
                nextItem = head;
                for (index = 0; index < i; index++) {
                    nextItem = nextItem.next;
                }
            }
        }

        /**
         * Construct a KWListIter that is a copy of another KWListIter
         * @param other The other KWListIter
         */
        public KWListIter(KWListIter other) {
            KWListIter itr = new KWListIter(0);
            itr.index = other.index;
            itr.lastItemReturned = other.lastItemReturned;
            itr.nextItem = other.nextItem;
        }

        /**
         * Indicate whether movement forward is defined.
         * @return true if call to next will not throw an exception
         */
        @Override
        public boolean hasNext() {												// θ(1)
            return nextItem != null;
        }

        /** Move the iterator forward and return the next item.
        @return The next item in the list
        @throws NoSuchElementException if there is no such object
         */
        @Override
        public E next() {															// θ(1)
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            lastItemReturned = nextItem;
            nextItem = nextItem.next;
            index++;
            return lastItemReturned.data;
        }

        /**
         * Indicate whether movement backward is defined.
         * @return true if call to previous will not throw an exception
         */
        @Override
        public boolean hasPrevious() {												// θ(1)
            return (nextItem == null && size != 0)
                    || nextItem.prev != null;
        }

        /**
         * Return the index of the next item to be returned by next
         * @return the index of the next item to be returned by next
         */
        @Override
        public int nextIndex() {																	// θ(1)
            return index;
        }

        /**
         * Return the index of the next item to be returned by previous
         * @return the index of the next item to be returned by previous
         */
        @Override
        public int previousIndex() {																		// θ(1)
            return index - 1;
        }

        /**
         * Move the iterator backward and return the previous item.
         * @return The previous item in the list
         * @throws NoSuchElementException if there is no such object
         */
        @Override
        public E previous() {																	// θ(1)
            if (!hasPrevious()) {
                throw new NoSuchElementException();
            }
            if (nextItem == null) { 
                nextItem = tail;
            } else {
                nextItem = nextItem.prev;
            }
            lastItemReturned = nextItem;
            index--;
            return lastItemReturned.data;
        }

        /**
         * Add a new item between the item that will be returned
         * by next and the item that will be returned by previous.
         * If previous is called after add, the element added is
         * returned.
         * @param obj The item to be inserted
         */
        @Override
        public void add(E obj) {													// θ(1)
            if (head == null) { 
                head = new Node<E>(obj);
                tail = head;
            } else if (nextItem == head) { 

                Node<E> newNode = new Node<E>(obj);

                newNode.next = nextItem; 

                nextItem.prev = newNode; 

                head = newNode; 
            } else if (nextItem == null) { 

                Node<E> newNode = new Node<E>(obj);

                tail.next = newNode; 

                newNode.prev = tail; 

                tail = newNode; 
            } else { 

                Node<E> newNode = new Node<E>(obj);

                newNode.prev = nextItem.prev; 
                nextItem.prev.next = newNode; 
                
                newNode.next = nextItem; 
                nextItem.prev = newNode; 
            }

            size++;
            index++;
            lastItemReturned = null;
        } 

        
        /** Remove the last item returned. This can only be
         *  done once per call to next or previous.
         *  @throws IllegalStateException if next or previous
         *  was not called prior to calling this method
         */
        @Override
        public void remove() {														// θ(1)
           lastItemReturned.prev.next = lastItemReturned.next;
           lastItemReturned.next.prev = lastItemReturned.prev;
        }

        
        /** Replace the last item returned with a new value
         *  @param item The new value
         *  @throws IllegalStateException if next or previous
         *  was not called prior to calling this method
         */
        @Override															// θ(1)
        public void set(E item) {
           lastItemReturned.data = item;
         }
       
    } 

    
    
	/** Returns a string representation of this collection. */
	@Override
	public String toString() 
	{
		return toString(" -- ");
	}
	
	public String toString(String interString) {								// θ(n^2)
		String text = new String();
		Iterator<E> it = iterator();
		while(it.hasNext()) 
			text += it.next() + interString;
		
		return text;
	}



	@Override
	public E find(E e) throws Exception {										// O(n)
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
  