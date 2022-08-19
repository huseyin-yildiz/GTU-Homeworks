import Containers.*;

/** Base Class for all Users (Administrators, BranchEmployees, Customers,etc.) */
public class User implements Identifiable {
	
	private static int idCounter = 0;
	private String name;
	private String surname;
	private String id;
	private String mail;
	private String password;
	private MyRepository myRepository;

	/** Constructor for generating base properties */
	public User( String name, String surname,
		String mail, String password) 
	{
			super();
			myRepository = MyRepository.getInstance();
			idCounter++;
			setId(Integer.toString( idCounter ));
			this.setName(name);
			this.setSurname(surname);
			this.setMail(mail);
			this.setPassword(password);
		
	}
	
	/** Constructor for getting the user with given Id. (Can be used like In searching)*/
	public User(String id) {
		setId(id);
	}


	/**
	 * @return the name
	 * returns the user's name
	 */
	public String getName() {
		return name;
	}


	/**
	 * @param name the name to set
	 * sets the user's name
	 */
	public void setName(String name) {
		this.name = name.toUpperCase();
	}


	/**
	 * @return the surname
	 * returns the user's surname
	 */
	public String getSurname() {
		return surname;
	}


	/**
	 * @param surname the surname to set
	 * Sets the user's surname
	 */
	public void setSurname(String surname) {
		this.surname = surname.toUpperCase();
	}

	/** returns name and surname */
	public String getFullName() {return getName() + " " + getSurname();}
	
	
	/**
	 * @return the id
	 * returns the user's id
	 */
	public String getId() {
		return id;
	}


	/**
	 * @param id the id to set
	 * Sets the user's id
	 */
	private void setId(String id) {
		this.id = id;
	}


	/**
	 * @return the mail
	 * returns the user's mail
	 */
	public String getMail() {
		return mail;
	}


	/**
	 * @param mail the mail to set
	 * Sets the user's mail
	 */
	public void setMail(String mail) {
		this.mail = mail;
	}


	/**
	 * @return the password
	 * Returns the user's password
	 */
	public String getPassword() {
		return password;
	}


	/**
	 * @param password the password to set
	 * Sets the user's password
	 */
	public void setPassword(String password) {
		this.password = password;
	}

	/** To get all Products in system */
	public IContainer<Product> getProducts() { return myRepository.getProducts(); }

	/** To search in products in all products */
	public IContainer<Product> searchProduct(String searchText) throws Exception {
		
		IContainer<Product> foundProducts = new MyList<Product>();
		
		Iterator<Product> it = myRepository.getProducts().iterator();
		while(it.hasNext()) {
			Product product = it.next(); 
			if(product.getModelName().contains(searchText.toUpperCase()) )
				foundProducts.add(product);
		}
		return foundProducts;
	}


	/**
	 * @return the myRepository
	 * returns the repository to access some data
	 */
	public MyRepository getRepository() {
		return myRepository;
	}

	/** Its overloaded to determine whether its same or not */
	@Override
	public boolean equals(Object obj) {
	
		if( obj instanceof User )
			return ((User)obj).getId().equals(this.getId());
		
		return false;
			
	}
	/** returns name and surname of the user as String */
	@Override
	public String toString() {
		return getId() +" | "+ getName() +" " + getSurname();
	}
	
	
}
