
import java.util.Iterator;

import Containers.*;

/**
 * 
 */

/**
 * @author Mehmet Huseyin Yildiz
 * The class for Customers
 */
public class Customer extends User {

	private IContainer<Order> myOrders;
	
	/**
	 * @param name
	 * @param surname
	 * @param mail
	 * @param password
	 */
	
	/** Initializes customers properties with given arguments */
	public Customer(String name, String surname, String mail, String password) {
		super(name, surname, mail, password);
		myOrders = new KWArrayList<Order>();
	}
	
	/** Initializes the id. Its used for some operations like searching */
	public Customer(String id) {																//  θ(1)
		super(id);
	}

	/** Orders a product with given order argument */
	public void orderProduct(Order order) throws Exception {									//  O(n^2)
		try{ getRepository().getCustomerById(this.getId()); } 
			catch (Exception e) { throw new Exception("The Customer is not added to system. Please add the customer before ordering."); } 
		
			Iterator<Product> it = order.getProducts().iterator();
			while(it.hasNext())
			{
				Product product = it.next();
				int stock = product.getAllStockSize();
				if(stock < 1)
					throw new Exception("The product "+product.getModelName()+" is not in stock" );
			}
		getRepository().addOrder(order);
	}
	
	/** Orders many products */
	public void orderProduct(IContainer<Product> products, String contactPhone, String contactAddress) throws Exception {							//  O(n^2)
		Order myOrder = new Order(products,contactPhone,contactAddress,this);
		orderProduct(myOrder);
	}
	
	/** gets all orders of the customer */
	public IContainer<Order> getMyOrders(){ return myOrders; } 							//  θ(1)


}
