package Containers;


/** The Interface for my myHashMap*/
public interface IHashMap<T, E> {

	/** Returns the key of the taken key */
	E get(T key) throws Exception;

	/** Returns all elements as IContainer*/
	IContainer<Twin<T, E>> getAll();

	/** Adds the taken key and value */
	void add(T key, E value) throws Exception;

	/** Removes the element by the key. Throws exception if its not found*/
	void remove(T key) throws Exception;

	/** Returns if the taken key is including or not */
	boolean contains(T key);

	/** Updates the value of the key */
	void update(T key, E value) throws Exception;

}