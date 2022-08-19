import Containers.*;

/** The class for Orders */

public class Order implements Identifiable {

	private final String id;
	private static int idCounter = 0;
	private IContainer<Product> products;
	private String phone;
	private String adress;
	private Customer customer;
	private boolean isDelivered;
	
	/** Initializes the fields by taking products , phone, address... */
	public Order( IContainer<Product> products, String phone, String adress, Customer customer) {
		
		super();
		id = generateId();
		this.products = products;			// product id kontrol et
		this.setPhone(phone);
		this.setAdress(adress);
		this.setCustomer(customer);
	}
	/** Initializes the fields by taking one product, phone, address... */
	public Order( Product product, String phone, String adress, Customer customer) {
		
			this(new MyList<Product>(), phone, adress, customer);
			products.add(product);
		}
	
	
	public Order(String id) {
		this.id = id;
	}
	
	private String generateId() {
		return Integer.toString( ++idCounter );
	}



	/**
	 * @return the phone
	 */
	public String getPhone() {
		return phone;
	}



	/**
	 * @param phone the phone to set
	 */
	public void setPhone(String phone) {
		this.phone = phone;
	}


	
	/**
	 * @return the adress
	 */
	public String getAdress() {
		return adress;
	}



	/**
	 * @param adress the adress to set
	 */
	public void setAdress(String adress) {
		this.adress = adress.toUpperCase();
	}


	
	/**
	 * @return the customer
	 */
	public Customer getCustomer() {
		return customer;
	}
	


	/**
	 * @param customer the customer to set
	 */
	public void setCustomer(Customer customer) {
		this.customer = customer;
	}


	
	/**
	 * @return the id
	 */
	public String getId() {
		return id;
	}



	/**
	 * @return the isDelivered
	 * to check whether the products is delivered or not
	 */
	public boolean isDelivered() {
		return isDelivered;
	}



	/**
	 * @param isDelivered the isDelivered to set
	 */
	public void setDelivered(boolean isDelivered) {
		this.isDelivered = isDelivered;
	}

	public IContainer<Product> getProducts(){
		return products;
	}
	
	@Override
	public boolean equals(Object obj) {
	
		if( obj instanceof User )
			return ((User)obj).getId().equals( this.getId() );
		
		return false;
			
	}
	
	/** returns the order information like name, phone, adress, products... */
	@Override
	public String toString() {
		return "Full Name:"+getCustomer().getFullName() + " | Products:" +products + " | Phone:" + getPhone() + " | Address:" + getAdress() + "  ";
	}
	
	
}
