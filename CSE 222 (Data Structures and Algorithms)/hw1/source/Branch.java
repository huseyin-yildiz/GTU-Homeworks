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
	private MyList<BranchEmployee> employees;
	private MyRepository repository;
	
	/**
	 * @throws Exception 
	 * Constructor that takes the name of branch
	 */
	public Branch(String name) throws Exception {
		id = Integer.toString(++idCounter);
		this.setName(name);
		employees = new MyList<BranchEmployee>();
		repository = MyRepository.getInstance();
		initializeStocks();
	}

	/**
	 * @return the id
	 */
	public String getId() {
		return id;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
	
	/** sets all products stocks in system as 0
	 * @throws Exception */
	private void initializeStocks() throws Exception {					
		Iterator<Product> it = repository.getProducts().iterator();
		while(it.hasNext())
			it.next().addStock(name, 0);
	}
	
	/** returns all employees of the branch */
	public IContainer<BranchEmployee> getEmployees(){
		return employees;
	}
	
	/** adds the BranchEmployee to the branch */
	public void addEmployee(BranchEmployee employee) throws Exception {
		if(! employees.add(employee))
			throw new Exception("There is already a branchEmployee in branch " + name + "with Id" +employee.getId() );
	}

	/** removes branch Employee */
	public void removeEmployee(BranchEmployee branchEmployee) throws Exception {
		if(! employees.remove(branchEmployee))
			throw new Exception("There is no such branchEmployee in branch " + name );
	}
	
	/** returns name of the branch as String */
	@Override
	public String toString() {
		return getName();
	}
	
	/** returns if its same branch or not with the given argument */
	@Override
	public boolean equals(Object obj) {
		if( obj instanceof Branch )
			return ((Branch)obj).getName().equals( this.getName() );
		
		return false;
	}

}
