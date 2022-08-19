import java.util.Iterator;

import Containers.*;

/**
 * 
 */

/**
 * @author dell
 * The base class for all products 
 */
public abstract class Product implements Identifiable  {

	private static int idCounter;	
	private final String id;
	private String modelName;
	private Color color;
	private float price;
	private IHashMap<String, Integer> stocks;				// Branch Id - stock number
	private MyRepository repository;
	
	/** Initializes the product */
	public Product( String modelName, Color color, float price) throws Exception {						//  θ(1)
		super();
		this.id = generateId();
		this.setModelName(modelName);
		this.setColor(color);
		this.setPrice(price);
		repository = MyRepository.getInstance();
		
		setUpStocks();
	}
	/** Initializes the product without color(used for multi colors) */
	public Product( String modelName, float price) throws Exception {						//  θ(1)
		this(modelName, Color.white, price);
	}
	
	
	public Product(String id) {
		this.id = id; 
	}
	
	/** Initializes the stocks for all branches as 0 */
	private void setUpStocks() throws Exception {						//  O(m*n)    m -> branchSize   n->productSize
		stocks = new MyHashMap<String, Integer>();
		Iterator<Branch> it = repository.getBranches().iterator();
		
		while(it.hasNext()) {
			String branchName = it.next().getName();
			
			try{stocks.add(branchName, 0);}
			catch (Exception e) {}
		}
	}
	
	private String generateId() {						//  θ(1)
		return Integer.toString( ++idCounter );
	}
	
	/** Returns the id of the product */
	public String getId() {						//  θ(1)
		return id;
	}

	/**
	 * @return the name
	 * Returns the model name
	 */
	public String getModelName() {						//  θ(1)
		return modelName;
	}

	/**
	 * @param modelName the modelName to set
	 */
	public void setModelName(String modelName) {						//  θ(1)
		this.modelName = modelName.toUpperCase();
	}

	/**
	 * @return the color
	 * Returns the color of the product
	 */
	public Color getColor() {						//  θ(1)
		return color;
	}

	/**
	 * @param color the color to set
	 * sets the color of the product
	 */
	public void setColor(Color color) {						//  θ(1)
		this.color = color;
	}
	
	/** returns the price of the product */
	public float getPrice() { return price; }						//  θ(1)
	
	/** sets the price of the product */
	public void setPrice(float price) { this.price = price; }						//  θ(1)

	/**
	 * @return the stock
	 * @throws Exception 
	 * returns the stock number in the taken branch 
	 */
	public int getStockInBranch(Branch branch) throws Exception {								//  O(m)		
		return stocks.get(branch.getName());
	}
	
	/** returns the all branch stock numbers of the product */
	public String getAllStocks() {																		//  θ(n^2*m)
		String stockText = new String();
		Iterator<Branch> branches = repository.getBranches().iterator();
		while(branches.hasNext()) {
			Branch branch = branches.next();
			try { stockText += ( branch.getName()+":" + stocks.get(branch.getName()) )+ " "; } 
				catch (Exception e) {}
		}
		return stockText;	
	}

	public int getAllStockSize() throws Exception{						//  θ(n^2)
		int size = 0;
		Iterator<Branch> branches = repository.getBranches().iterator();
		while(branches.hasNext()) {
			Branch branch = branches.next();
			size += stocks.get(branch.getName()) ;
		}
		return size;
	}

	/**
	 * @param stock the stock to set
	 * @throws Exception 
	 * changes the stock of a prodcut in a branch
	 */
	public void updateStock(String branchName,int stock) throws Exception {							//  O(n)
			
			stocks.update(branchName, stock);
			
		
	}
	/** increases the stock of the product in a branch*/
	public void addStock(String branchName, int stock) throws Exception {						//  O(1)
		if(! stocks.contains(branchName))
			stocks.add(branchName, stock);
	}
	
	/** To compare if they are same product or not */
	@Override
	public boolean equals(Object obj) {																//  θ(1)
	
		boolean flag = false;
		if( obj instanceof Product )
				flag = ((Product)obj).getId().equals(getId());
			
		return flag;
			
	}
	
	/** returns the information about the product like model name,stocks in branches or color */
	@Override
	public String toString() {						//  θ(n^2)
		return getModelName() + " | " +getColor() + " | Stocks: " + getAllStocks() +" ||| ";
	}
	
	
}
