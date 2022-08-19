import java.util.Iterator;

import Containers.*;

/**
 * 
 */

/**
 * @author dell
 * The class for branches
 */
public class Branch implements Identifiable{

	private static int idCounter = 0;
	private String id;
	private String name;
	private KWArrayList<BranchEmployee> employees;
	private MyRepository repository;
	
	/**
	 * @throws Exception 
	 * Constructor that takes the name of branch
	 */
	public Branch(String name) throws Exception {
		id = Integer.toString(++idCounter);
		this.setName(name);
		employees = new KWArrayList<BranchEmployee>();
		repository = MyRepository.getInstance();
		initializeStocks();
	}

	/**
	 * @return the id
	 */
	public String getId() {							//  θ(1)
		return id;
	}

	/**
	 * @return the name
	 */
	public String getName() {							//  θ(1)
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {							//  θ(1)
		this.name = name;
	}
	
	/** sets all products stocks in system as 0
	 * @throws Exception */
	private void initializeStocks() throws Exception {											//  O(n)	
		Iterator<Product> it = repository.getProducts().iterator();
		while(it.hasNext())
			it.next().addStock(name, 0);
	}
	
	/** returns all employees of the branch */
	public IContainer<BranchEmployee> getEmployees(){										//  θ(1)
		return employees;
	}
	
	/** adds the BranchEmployee to the branch */
	public void addEmployee(BranchEmployee employee) throws Exception {								//  θ(1)
		if(! employees.add(employee))
			throw new Exception("There is already a branchEmployee in branch " + name + "with Id" +employee.getId() );
	}

	/** removes branch Employee */
	public void removeEmployee(BranchEmployee branchEmployee) throws Exception {						//  O(1)
		if(! employees.remove(branchEmployee))
			throw new Exception("There is no such branchEmployee in branch " + name );
	}
	
	/** returns name of the branch as String */
	@Override
	public String toString() {													//  θ(1)
		return getName();
	}
	
	/** returns if its same branch or not with the given argument */
	@Override
	public boolean equals(Object obj) {							//  θ(1)
		if( obj instanceof Branch )
			return ((Branch)obj).getName().equals( this.getName() );	// assume as θ(1)
		
		return false;
	}

}
