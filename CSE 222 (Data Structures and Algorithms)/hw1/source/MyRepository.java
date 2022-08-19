
import Containers.*;

/**
 * 
 */

/**
 * @author dell
 *
 */
public class MyRepository implements IRepository {

	private static MyRepository myRepository;
	
	private MyList<Customer> customers;
	private MyList<Administrator> administrators;
	private MyList<Product> products;
	private MyList<Order> orders;
	private MyList<Branch> branches;
	private MyList<Message> messages;
	
	/**
	 * 
	 */
	
	private MyRepository() {
		
		customers = new MyList<Customer>();
		administrators = new MyList<Administrator>();
		products = new MyList<Product>();
		orders = new MyList<Order>();
		branches = new MyList<Branch>();
		messages = new MyList<Message>();
		
	}
	
	public static MyRepository getInstance() {
		if(myRepository == null)
			myRepository = new MyRepository();
		return myRepository;
	}

	@Override
	public IContainer<Customer> getCustomers() { return customers; }


	@Override
	public IContainer<Administrator> getAdministrators() { return administrators; }

	@Override
	public IContainer<Product> getProducts() { return products;	}

	@Override
	public IContainer<Order> getOrders() { return orders;	}

	@Override
	public IContainer<Branch> getBranches() { return branches;}
	
	
	
	@Override
	public void addUser(User user) throws Exception { 
		
		if (user instanceof Customer)
			customers.add((Customer) user);
		else if (user instanceof BranchEmployee)
			{
				BranchEmployee branchEmployee = (BranchEmployee) user;
				if(! branches.contains( branchEmployee.getBranch()) )
					throw new Exception("The given branch is not found in system please add the branch before adding Branch Employee");
				
				branchEmployee.getBranch().addEmployee(branchEmployee);
			}
		else if (user instanceof Administrator)
			administrators.add((Administrator) user);
		else
			throw new Exception("The given argument is not valid");
	}

	@Override
	public void addProduct(Product product) {
		products.add(product);
	}

	@Override
	public void addOrder(Order order) throws Exception  {
		 Customer customer = getCustomerById(order.getCustomer().getId());
		 customer.getMyOrders().add(order); 
		
		 orders.add(order);
		 
	}

	@Override
	public void removeUser(User user) throws Exception {
		if (user instanceof Customer)
			customers.remove((Customer) user);
		else if (user instanceof BranchEmployee)
		{
			BranchEmployee branchEmployee = (BranchEmployee) user;
			branchEmployee.getBranch().removeEmployee(branchEmployee);
		}
		else if (user instanceof Administrator)
			administrators.remove( (Administrator) user);
		else
			throw new Exception("The given argument is not valid");

	}

	@Override
	public void removeProduct(Product product) throws Exception{
		products.remove(product);
	}

	@Override
	public void removeOrder(Order order) throws Exception{
		orders.remove(order);
	}

	@Override
	public void updateUser(User user) throws Exception {
		removeUser(user);
		addUser(user);
	}

	@Override
	public void updateProduct(Product product) throws Exception{
		removeProduct(product);
		addProduct(product);
	}

	@Override
	public void updateOrder(Order order) throws Exception{
		removeOrder(order);
		addOrder(order);
	}

	@Override
	public Customer getCustomerById(String id) throws Exception{
		try {
			Identifiable user = new Customer(id);
			return customers.find((Customer) user);
		}catch (Exception e) {
			throw new Exception("Couldn't find the Customer with the given Id ");
		}
		
	}

	@Override
	public Employee getEmployeeById(String id) throws Exception{
		Identifiable user = new User(id);
		Iterator<Branch> it = branches.iterator();
		
		while(it.hasNext()) {
		Branch branch = it.next();
		Iterator<BranchEmployee> it1 = branch.getEmployees().iterator();
			while(it1.hasNext())
			{
				BranchEmployee branchEmployee = it1.next();
				if(branchEmployee.getId().equals(id))
					return branchEmployee;
			}
		}
		throw new Exception("Couldn't find the Employee with the given Id ");
	}

	@Override
	public Administrator getAdministratorById(String id) throws Exception{
		Identifiable user = new User(id);
		return administrators.find((Administrator) user);
	}

	@Override
	public Product getProductById(String id) throws Exception{
		Identifiable product = new Product(id) {};
		try {
			return products.find((Product) product);}
		catch (Exception e) {
			throw new Exception("Couldnt find the product with that id !");
		}
		
	}

	@Override
	public Order getOrderById(String id) throws Exception {
		Identifiable order = new Order(id);
		try { return orders.find((Order) order); }
		catch(Exception e) { throw new Exception("The given branch is not found in system please add the branch before adding Branch Employee"); }
		 
		
	}


	

	@Override
	public void addBranch(Branch branch) {	
		branches.add(branch); 
	}

	@Override
	public void removeBranch(Branch branch) throws Exception { 
			
			Iterator<Product> it = products.iterator();
			while( it.hasNext() )
			{
				int productStockSize = it.next().getStockInBranch(branch);
				if(productStockSize > 0)
					throw new Exception("The branch has products in stock. You must remove or change them before. " );
			}
			
			if(branch.getEmployees().size() > 0)
				throw new Exception("The branch has employees. You must remove or change thems branch before. " );
			else
				branches.remove(branch); 
		}

	@Override
	public void updateBranch(Branch branch) throws Exception { branches.remove(branch); }

	@Override
	public Branch getBranchByName(String branchName) throws Exception {
		Iterator<Branch> it = branches.iterator();
		while(it.hasNext())
		{
			Branch branch = it.next();
			if(branch.getName().equals(branchName))
				return branch;
		}
		throw new Exception("Couldn't find the branch with the given name");
	}

	@Override
	public User login(String mail, String password) throws Exception {
		
		Iterator<User> it = getUsers().iterator();
		while(it.hasNext())
		{
			User user = it.next();
			if( user.getMail().equals(mail)  && user.getPassword().equals(password) )
				return user;
				
		}
		throw new Exception("The given E-mail or password is not correct");
	}

	@Override
	public IContainer<User> getUsers() {
		MyList<User> users = new MyList<User>();
		
		Iterator<Administrator> it = getAdministrators().iterator();
		while(it.hasNext()) {
			users.add(it.next());
		}
		
		Iterator<Customer> it1 = getCustomers().iterator();
		while(it1.hasNext()) {
			users.add(it1.next());	
		}
		
		
		Iterator<Branch> it2 = getBranches().iterator();
		while(it2.hasNext()) {
			Iterator<BranchEmployee> it3 = it2.next().getEmployees().iterator();
			while(it3.hasNext()) {
				users.add(it3.next());
			}
			
		}
		
		return users;
	}

	@Override
	public IContainer<Message> getMessages() {
		return messages;
	}

	@Override
	public void addMessage(Message message) {
		messages.add(message);
	}
	
	

}
