import java.util.Iterator;

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
	public User( String name, String surname,													//  θ(1)
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
	public User(String id) {						//  θ(1)
		setId(id);
	}


	/**
	 * @return the name
	 * returns the user's name
	 */
	public String getName() {						//  θ(1)
		return name;
	}


	/**
	 * @param name the name to set
	 * sets the user's name
	 */
	public void setName(String name) {						//  θ(1)
		this.name = name.toUpperCase();
	}


	/**
	 * @return the surname
	 * returns the user's surname
	 */
	public String getSurname() {						//  θ(1)
		return surname;
	}


	/**
	 * @param surname the surname to set
	 * Sets the user's surname
	 */
	public void setSurname(String surname) {						//  θ(1)
		this.surname = surname.toUpperCase();
	}

	/** returns name and surname */
	public String getFullName() {return getName() + " " + getSurname();}						//  θ(1)
	
	
	/**
	 * @return the id
	 * returns the user's id
	 */
	public String getId() {						//  θ(1)
		return id;
	}


	/**
	 * @param id the id to set
	 * Sets the user's id
	 */
	private void setId(String id) {						//  θ(1)
		this.id = id;
	}


	/**
	 * @return the mail
	 * returns the user's mail
	 */
	public String getMail() {						//  θ(1)
		return mail;
	}


	/**
	 * @param mail the mail to set
	 * Sets the user's mail
	 */
	public void setMail(String mail) {						//  θ(1)
		this.mail = mail;
	}


	/**
	 * @return the password
	 * Returns the user's password
	 */
	public String getPassword() {						//  θ(1)
		return password;
	}


	/**
	 * @param password the password to set
	 * Sets the user's password
	 */
	public void setPassword(String password) {						//  θ(1)
		this.password = password;
	}

	/** To get all Products in system */
	public IContainer<Product> getProducts() { return myRepository.getProducts(); }						//  θ(1)

	/** To search in products in all products */
	public IContainer<Product> searchProduct(String searchText) throws Exception {						//  O(m*n) m->productSize n-> searchText Size
		
		IContainer<Product> foundProducts = new KWArrayList<Product>();
		
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
	public MyRepository getRepository() {						//  θ(1)
		return myRepository;
	}

	/** Its overloaded to determine whether its same or not */
	@Override
	public boolean equals(Object obj) {						//  θ(1)
	
		if( obj instanceof User )
			return ((User)obj).getId().equals(this.getId());
		
		return false;
			
	}
	/** returns name and surname of the user as String */
	@Override
	public String toString() {						//  O(n^2)
		return getId() +" | "+ getName() +" " + getSurname();
	}
	
	
}
