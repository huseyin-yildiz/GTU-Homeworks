import Containers.*;

/**
 * 
 */

/**
 * @author dell
 * The Class for Employees of branch
 */
public class BranchEmployee extends Employee {
	
	private Branch branch;

	
	/**
	 * @param name
	 * @param surname
	 * @param mail
	 * @param password
	 * @throws Exception 
	 */
	public BranchEmployee(String branchName, String name, String surname, String mail, String password) throws Exception {
		super(name, surname, mail, password);
		this.branch = getRepository().getBranchByName(branchName);
	}
	
	/** increases the stock of the given product in the branch of the branch employee*/
	public void addProductStock (Product product,int size ) throws Exception {
		int oldStock = product.getStockInBranch(branch);
		int newStock = oldStock + size;
		product.updateStock(getBranch().getName(),newStock);
	}
	
	/** adds product to the system */
	public void addProduct(Product product, int stockSize) throws Exception {
		addProduct(product);
		product.updateStock(getBranch().getName(), stockSize);
	}
	
	/** makes a new sale by passing the order as argument and makes it delivered 
	 * @throws Exception */
	public void makeSale(Order order) throws Exception {
		Iterator<Product> it = order.getProducts().iterator();
		while(it.hasNext())
		{
			Product product = it.next();
			int stock = getStockOfProduct(product);
			if(stock < 1)
				throw new Exception("The product "+product.getModelName()+" is not in stock" );
		}

		it = order.getProducts().iterator();
		while(it.hasNext())
		{
			Product product = it.next();
			Branch branch = getBranch();
			product.updateStock(branch.getName(),product.getStockInBranch(branch)-1);
		}

		order.setDelivered(true);
		getRepository().addOrder(order);
	}

	
	/**
	 * @return the branch
	 *  get the branch of the branch employee
	 */
	public Branch getBranch() {
		return branch;
	}

	/** returns stock of the given product as parameter */
	public int getStockOfProduct(Product product) throws Exception {
		return product.getStockInBranch( this.getBranch() );
	}
	
	/** informs administrator about a product with required amount */
	public void informAdmin(String ProductId, int requiredAmount) throws Exception {
		Product product = getRepository().getProductById(ProductId);
		String text = "We need "+ requiredAmount +" "+ product.getColor() +" "+ product.getModelName()+" whose Id:"
				+ product.getId() +" In Branch: " + this.getBranch().getName() ;
		Message message = new Message(text, this);
		getRepository().addMessage(message);
	}

}
