package Containers;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class HybridList<E> implements IContainer<E> {

	private LinkedList< ArrayList<E> > linkedList;
	private int MAX_NUMBER;
	private int size ;
	
	public HybridList() {
		
		MAX_NUMBER = 10;
		size = 0;	
		linkedList = new LinkedList<ArrayList<E>>();	
		linkedList.add( new ArrayList<E>() );
	}

	private class HybritIterator implements ListIterator<E> {

		private ListIterator<ArrayList<E>> linkedListIterator;
		private ListIterator<E> arrayListIterator;
		private ArrayList<E> lastReturnedArrayList;		
		private int index;
		

		public HybritIterator(int i){
			index = 0;
			if(i > size || i < 0)
				throw new IndexOutOfBoundsException();
			
			else if(size == i)
			{
				int linkedListSize = linkedList.size();
				linkedListIterator = linkedList.listIterator(linkedListSize-1);											// !!!!!! burası listSize -1 olabilir
				ArrayList<E> lastArrList = linkedListIterator.next();
				
				lastReturnedArrayList = lastArrList;
				
				int arrListSize = lastArrList.size();
				arrayListIterator = lastArrList.listIterator(arrListSize);
				index = size;
			}
			else {
				
				linkedListIterator = linkedList.listIterator(0);
				
				lastReturnedArrayList = linkedListIterator.next();
				arrayListIterator = lastReturnedArrayList.listIterator();
				
				while(nextIndex() != i)
				{
					next();
				}
					
			}
		}
				
		@Override
		public void add(E item) {
			
			if(arrayListIterator.hasNext())										
			{
				if(nextIndex() == 0)											// if its at first and has next
				{
					ArrayList<E> newArrayList = new ArrayList<E>();
					newArrayList.add(item);
					
					if(linkedListIterator.hasPrevious())
					{
						linkedListIterator.previous();
						linkedListIterator.add(newArrayList);
					}
					else 
						linkedList.addFirst(newArrayList);
					
				}
				else															// if its at the middle 
				{
					if(lastReturnedArrayList.size() != MAX_NUMBER)
						arrayListIterator.add(item);
					else
					{
						E lastItem = lastReturnedArrayList.remove( MAX_NUMBER-1 );
						arrayListIterator.add(item);
						
						ArrayList<E> nextArrayList = new ArrayList<E>();
						nextArrayList.add(lastItem);
						linkedListIterator.add(nextArrayList);
					}
				}
			}
			
			else if( nextIndex() == MAX_NUMBER)										// if its at the end
			{
					ArrayList<E> nextArrayList = new ArrayList<E>();
					nextArrayList.add(item);
					linkedListIterator.add(nextArrayList);
			}
							
			else
				arrayListIterator.add(item);			
			size++;
		}

		@Override
		public boolean hasNext() {
			if( arrayListIterator != null && arrayListIterator.hasNext() )
				return true;
			return linkedListIterator.hasNext();
		}
		

		@Override
		public boolean hasPrevious() {
			if( arrayListIterator != null && arrayListIterator.hasPrevious() )
				return true;
			return linkedListIterator.hasPrevious();
		}

		@Override
		public E next() {
			if( arrayListIterator != null && arrayListIterator.hasNext() )
			{
				index++;
				return arrayListIterator.next();
			}
			if(linkedListIterator.hasNext())
			{
				lastReturnedArrayList = linkedListIterator.next();
				arrayListIterator = lastReturnedArrayList.listIterator();
				index++;
				return arrayListIterator.next();
			}
			else
				throw new NoSuchElementException();
			
		}

		@Override
		public int nextIndex() {
			return index;
		}

		@Override
		public E previous() {
			if( arrayListIterator != null && arrayListIterator.hasPrevious() )
			{
				index--;
				return arrayListIterator.previous();
			}
			if( linkedListIterator.hasPrevious() )
			{
				ArrayList<E> previousArray = linkedListIterator.previous();
				lastReturnedArrayList = previousArray;
				int size = previousArray.size();
				arrayListIterator = previousArray.listIterator(size);
				index--;
				return arrayListIterator.next();											// !!!!!!!!!!! hata olabilir
			}
			else
				throw new NoSuchElementException();
		}

		@Override
		public int previousIndex() {
			return index-1;
		}

		@Override
		public void remove() {
			if(arrayListIterator != null)
				arrayListIterator.remove();
			if(lastReturnedArrayList.size() == 0)
				linkedListIterator.remove();
			size--;
		}

		@Override
		public void set(E item) {
			arrayListIterator.set(item);
			
		}
		
	}
	
	
	
	public void add(int index, E element) {
		listIterator(index).add(element);
	}
	
	public boolean add(E element) {
		add(size,element);
		return true;
	}

	public boolean addAll(Collection<E> collection) {
		return addAll(size,collection);
	}

	public boolean addAll(int index, Collection<E> collection) {
		ListIterator<E> it1 = listIterator(index);
		Iterator<E> it2 = collection.iterator();
		while(it2.hasNext() )
			 it1.add(it2.next());
		return true;
	}

	
	public void clear() {
		linkedList.clear();
		linkedList.add(new ArrayList<E>());
		size = 0;
	}

	@Override
	public boolean contains(Object item) {
		ListIterator<E> it = listIterator();
		while(it.hasNext())
		{
			if(it.next().equals(item))
				return true;
		}
		return false;
	}

	public boolean containsAll(Collection<E> collection) {
		Iterator<E> it = collection.iterator();
		while(it.hasNext()) {
			if( ! contains(it.next()) )
				return false;
					
		}
		return true;
	}


	public E get(int index) {
		return listIterator(index).next();
	}

	public int indexOf(Object item) {
		ListIterator<E> it = listIterator();
		while(it.hasNext())
			if(it.next().equals(item))
				return it.nextIndex()-1;
		return -1;
	}

	@Override
	public boolean isEmpty() {
		return size == 0;
	}

	@Override
	public Iterator<E> iterator() {
		return listIterator();
	}


	public ListIterator<E> listIterator() {
		return listIterator(0);
	}

	public ListIterator<E> listIterator(int index) {
		return new HybritIterator(index);
	}

	
	public boolean remove(Object item) {
		ListIterator<E> it = listIterator();
		while(it.hasNext())
			if(it.next().equals(item))
			{
				it.remove();
				return true;
			}
		return false;
	}

	public E remove(int index) {
		ListIterator<E> it = listIterator(index);
		E item = it.next();
		it.remove();
		return item;
	}

	public boolean removeAll(Collection<E> collection) {
		Iterator<E> it = collection.iterator();
		while(it.hasNext())
			remove(it.next());
		return true;
	}


	public E set(int index, E item) {
		ListIterator<E> it = listIterator(index);
		it.next();
		it.set(item);
		return item;
	}

	@Override
	public int size() {
		return size;
	}

	 
	/** Returns a string representation of this collection. */
	@Override
	public String toString() 
	{
		return toString(" -- ");
	}
	
	public String toString(String interString) {
		String text = new String();
		ListIterator<E> it = listIterator();
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

		
	public static void main(String[] args) throws Exception {
		HybridList<String> a = new HybridList<String>();
		a.add("ali");

		ListIterator<String> it = a.listIterator(0);
		System.out.println(it.hasNext());
		System.out.println(it.next());
		it.add("veli");
		it = a.listIterator();
		it.next();
		System.out.println("next1 "+ it.next());
		System.out.println( a );
		
		System.out.println(it.previous());
		System.out.println( a );
		
		System.out.println( it.nextIndex() );
		System.out.println("1: "+ a );
		
		it.add("zeki");
		System.out.println("2: "+ a);
		
		System.out.println(a.contains("zeki"));
		a.remove("zeki");
		System.out.println(a.contains("zeki"));
		a.clear();
		a.add("asd");
		System.out.println(a);
		a.add("qwe");
		a.add("qwqwase");
		
		System.out.println( a.isEmpty());
		
		System.out.println(a);
		System.out.println( a.indexOf("asd") );
		System.out.println( a.indexOf("qwe") );
		System.out.println( a.indexOf("qwqwase") );
		
		a.remove(1);
		System.out.println(a);
		
		
	//	System.out.println(it.previous());
		
		
	//	System.out.println(a.toString() );
	}
		
}
