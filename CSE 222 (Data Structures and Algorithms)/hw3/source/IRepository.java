import Containers.*;

/*
 * The Inteface for Repository of the system that holds all things together.
 */
public interface IRepository {

	/** returns all customer in IContainer type */
	public IContainer<Customer> getCustomers();
	
	/** returns all customers in IContainer type */
	public IContainer<Administrator> getAdministrators();
	
	/** returns all products in IContainer type */
	public IContainer<Product> getProducts();
	
	/** returns all orders in IContainer type */
	public IContainer<Order> getOrders();
	
	/** returns all branches in IContainer type */
	public IContainer<Branch> getBranches();
	
	/** returns all users in IContainer type */
	public IContainer<User> getUsers();
	
	/** returns all messages(Like informing th administrator about require product) in IContainer type */
	public IContainer<Message> getMessages();
	
	/** adds the taken user to repository */
	public void addUser(User user) throws Exception;
	
	/** adds the taken user to repository */
	public void addProduct(Product product);
	
	/** adds the taken order to repository */
	public void addOrder(Order order) throws Exception;
	
	/** adds the taken branch to repository */
	public void addBranch(Branch branch);
	
	/** adds the taken message to repository */
	public void addMessage(Message message);
	
	/** removes the taken user to repository */
	public void removeUser(User user) throws Exception;
	
	/** removes the taken product to repository */
	public void removeProduct(Product product) throws Exception;
	
	/** removes the taken order to repository */
	public void removeOrder(Order order) throws Exception;
	
	/** removes the taken branch to repository */
	public void removeBranch(Branch branch) throws Exception;
	
	/** updates the taken user in repository (finds the old one by id) */
	public void updateUser(User user) throws Exception;
	
	/** updates the taken product in repository (finds the old one by id) */
	public void updateProduct(Product product) throws Exception;
	
	/** updates the taken order in repository (finds the old one by id) */
	public void updateOrder(Order order) throws Exception;
	
	/** updates the taken branch in repository (finds the old one by name) */
	public void updateBranch(Branch branch) throws Exception;
	
	/** updates the taken user in repository (finds the old one by id) */
	public Customer getCustomerById(String id) throws Exception;
	
	/** finds and returns the employee by id in repository  */
	public Employee getEmployeeById(String id) throws Exception;
	
	/** finds and returns the administrator by id in repository  */
	public Administrator getAdministratorById(String id) throws Exception;
	
	/** finds and returns the product by id in repository  */
	public Product getProductById(String id) throws Exception;
	
	/** finds and returns the order by id in repository  */
	public Order getOrderById(String id) throws Exception;
	
	/** finds and returns the branch by id in repository  */
	public Branch getBranchByName(String branchName) throws Exception;
	
	/** takes mail and password and returns user if they are true */
	public User login(String mail, String password) throws Exception;

	
}
