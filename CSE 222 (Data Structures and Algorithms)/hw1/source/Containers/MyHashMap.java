package Containers;

/** My own HashMap class */
public class MyHashMap<T,E> implements IHashMap<T, E> {

	MyList<Twin<T,E>> list;
	
	public MyHashMap() {
		list = new MyList<Twin<T,E>>();
	}
	
	
	@Override
	public E get(T key) throws Exception{
		Iterator<Twin<T, E>> it = list.iterator();
		while(it.hasNext())
		{
			Twin<T, E> element = it.next();
			if(element.getFirst().equals(key) ){
				return element.getSecond();
			}
		}
		throw new Exception("There is no element with given key");
	}
	
	@Override
	public MyList<Twin<T, E>> getAll() {
		return list;
	}
	
	@Override
	public void add(T key, E value) throws Exception {
		if(!contains(key))
			list.add(new Twin<T, E>(key, value));
		else
			throw new Exception("The given key already exist");
	}
	
	@Override
	public void remove(T key) throws Exception
	{
		try {
			E value = get(key);
			list.remove(new Twin<T, E>(key, value));
		} catch (Exception e) {
			throw e;
		}
	}
	
	@Override
	public boolean contains(T key) {
		try {
			get(key);
			return true;
		} catch (Exception e) {
			return false;
		}
	}
	
	@Override
	public void update(T key, E value) throws Exception {
		Iterator<Twin<T,E>> it = list.iterator(); 
		
		while(it.hasNext())
		{
			Twin<T,E> element = it.next();
			if(element.getFirst().equals(key))
				{
					element.setSecond(value);
					return;
				}
		}
		throw new Exception("There is no element with given key");
	}

}