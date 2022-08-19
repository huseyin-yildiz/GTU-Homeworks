package Containers;

import java.util.Iterator;

/** The interface for my own container to hold and process data */
public interface IContainer<E> {

	/** adds the taken element. returns true if succeeded */
	boolean add(E e);

	/** adds the all taken elements (as IContainer). returns true if succeeded */
//	boolean addAll(IContainer<E> c);

	/** removes all elements. */
	void clear();

	/** returns if it contains the taken element or not. */
	boolean contains(E e);

	/** returns if it contains the all elements (as IContainer) or not. */
//	boolean containsAll(IContainer<E> c);

	/** returns if empty or not */
	boolean isEmpty();

	/** removes the taken element. returns if succeeded or not*/
	boolean remove(E e);

	/** removes all elements (as IContainer). returns if succeeded or not*/
//	boolean removeAll(IContainer<E> c);

	/** removes all those not in the taken IContainer.*/
//	boolean retainAll(IContainer<E> c);
	
	/** finds the taken element and return it. */
	E find(E e) throws Exception;

	/** returns the size of elements*/
	int size();

	/** returns an iterator */
	Iterator<E> iterator();

	/** Returns a string representation of this collection. */
	String toString();
	
	/** Returns a string representation of this collection with putting the string between them . */
	String toString(String string);

}