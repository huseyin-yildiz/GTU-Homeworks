package Containers;

/** The class for hold generic twins  */
public class Twin<T,E> {

	private T first;
	private E second;
	
	/** takes the first and second value as generic and initializes */
	public Twin(T first, E second) {
		setFirst(first);
		setSecond(second);
	}

	/**
	 * @return the first
	 * Returns the first element
	 */
	public T getFirst() {
		return first;
	}

	/**
	 * @param first the first to set
	 * Sets the first element
	 */
	public void setFirst(T first) {
		this.first = first;
	}

	/**
	 * @return the second
	 * Returns the second element
	 */
	public E getSecond() {
		return second;
	}

	/**
	 * @param second the second to set
	 * Sets the first element
	 */
	public void setSecond(E second) {
		this.second = second;
	}

}
