import java.util.Iterator;

import Containers.*;

/**
 * 
 */

/**
 * @author dell
 * The class for all employees
 */
public abstract class Employee extends User{
	
	private IRepository repository;
		
	/** adds new Product 
	 * @throws Exception */
	public void addProduct(Product product) throws Exception{							//  θ(1)
		if(repository.getProducts().contains(product))
			throw new Exception("The product already exist. You can not add it again");
		repository.addProduct(product);
	}
	
	public void addProducts(Product product,IContainer<Color> colors) throws Exception{							//  O(n)
		Iterator<Color> it = colors.iterator();
		while(it.hasNext()) {
			Product product2 = new Product(product.getModelName(),it.next(),product.getPrice()) {} ;
			addProduct(product2);
		}
	}
	
	/** removes the Product  */
	public void removeProduct(Product product)throws Exception {							//  O(n)
		repository.removeProduct(product);
	}
	
	
	
	/** gives the last Orders of the Customer   */
	public IContainer<Order> getOrdersOfCustomer(String customerId) throws Exception{								//  O(n^2)
		return repository.getCustomerById(customerId).getMyOrders(); }
	
	/** makes a new order and make it not delivered 
	 * @throws Exception */
	public void addOrder(Order order) throws Exception {							//  θ(1)
		repository.addOrder(order);
	}
	
	/** adds a new customer to system  */
	public void makeSubscription(Customer customer) throws Exception {							//  θ(1)
		repository.addUser(customer);
	}
	
	
	/** Constructor that fill the the given properties */
	public Employee(String name, String surname, String mail, String password) {
			
		super(name, surname, mail, password);
		repository = getRepository();
	}



}
