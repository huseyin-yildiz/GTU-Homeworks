package Containers;

/** The class that implements IContainer to hold some data and process them */
public class MyList<E> implements  IContainer<E> {
	
	private Object[] array ;
	private int capacity;
	private int used;
	
	/** Initializing the required fields */
	public MyList() {
		capacity = 10;
		array = new Object[capacity];
		used = 0;
	}
	
	
	private void increaseCapacity(int size) 
	{
		int oldCapacity = capacity;
		Object[] temp = array;
		capacity += size;
		array = new Object[capacity];
		
		for(int i=0; i<oldCapacity; i++)			// copying all old values
			array[i] = temp[i];
	}
	
	@Override
	public boolean add(E e) 
	{
		if(capacity == used)
			increaseCapacity(5);
		
		array[used] = e;
		used++;
		return true;
	}

	@Override
	public boolean addAll(IContainer<E> c) 
	{
		Iterator<E> it = c.iterator();
		while(it.hasNext())
			add(it.next());
		
		return true;
	}

	@Override
	public void clear() 
	{
		capacity = 10;
		used = 0;
		array = new Object[capacity];
	}

	@Override
	public boolean contains(E e) 
	{
		Iterator<E> it = iterator();
		while(it.hasNext())
			if(it.next().equals(e))
				return true;
		return false;
	}

	@Override
	public boolean containsAll(IContainer<E> c) 
	{
		Iterator<E> it = c.iterator();
		while(it.hasNext())
			if(! contains(it.next()))
				return false;
		return true;
	}

	@Override
	public boolean isEmpty() 
	{
		return used == 0;
	}
	
	@Override
	public boolean remove(E e) 
	{
		if(! contains(e))
			return false;
		
		Object newArr[] = new Object[capacity];
		int i = 0;
		boolean found = false;
		
		Iterator<E> it = iterator();
		while(it.hasNext()) 
		{
			E element = it.next();
			
			if(element != e || found)
			{
				newArr[i] = element;
				i++;
			}
			else
				found = true;
		}

		used--;
		array = newArr;
		return true;
	}
	
	@Override
	public boolean removeAll(IContainer<E> c) 
	{
		Iterator<E> it = c.iterator();
		
		while(it.hasNext())
			remove(it.next());
		return true;
	}

	@Override
	public boolean retainAll(IContainer<E> c) 
	{
		Iterator<E> it = iterator();
		while(it.hasNext())
		{
			E element = it.next();
			if(! c.contains(element))
				remove(element);
		}
		return true;
	}
	
	@Override
	public int size() 
	{
		return used;
	}
	
	@Override
	public Iterator<E> iterator() 
	{
		return new Iterator<E>() {
			
			int current = -1;
			
			@Override
			public boolean hasNext() 
			{
				return current < (used-1);
			}

			@Override
			public E next() 
			{
				current++;
				return (E) array[current];
			}

			@Override
			public void remove() 
			{
				E element = (E)array[current];
				MyList.this.remove(element);
			}
		};
	}
	

	/** Returns a string representation of this collection. */
	@Override
	public String toString() 
	{
		return toString(" -- ");
	}
	
	public String toString(String interString) {
		String text = new String();
		Iterator<E> it = iterator();
		while(it.hasNext()) 
			text += it.next() + interString;
		
		return text;
	}


	@Override
	public E find(E e) throws Exception {
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

