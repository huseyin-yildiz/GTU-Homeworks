package Containers;

/** An iterator over a collection. */
public interface Iterator<T> {
	
	/** Returns true if the iteration has more elements. */
	public boolean hasNext();
	
	/** Returns the next element in the iteration. */
	public T next();

	/** Removes from the underlying collection the last element returned by this iterator */
	public void remove() throws Exception;
}