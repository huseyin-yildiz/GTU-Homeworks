import java.util.Scanner;

import Containers.IContainer;
import Containers.Iterator;

/** The class for interactive console interface that includes required menus */
public class ConsoleMenu {

	private MyRepository repository;
	private User currentUser;											
	
	/** Constructor */
	public ConsoleMenu() {
		repository = MyRepository.getInstance();
		
	}
	
	/** Shows the first menu for login and signup */
	public void mainMenu() throws Exception {
		System.out.println("Welcome To Our Furniture Store");
		System.out.println("1- Log in");
		System.out.println("2- Sign Up");
	
		Scanner scanner = new Scanner(System.in);
		int selection = 0;
		selection = scanner.nextInt();
		
		switch (selection) {
			case 1: currentUser = loginMenu();  break;
			case 2: currentUser = signUpMenu(); break;
			default: System.out.println("Wrong selection please try again."); mainMenu(); 
		}
		
		currentUserMenu();
		
	}


	/** shows the menu for current logged in user operations*/
	public void currentUserMenu() throws Exception {
		
		if(currentUser instanceof Customer)	{
			customerMenu();
		}
		else if(currentUser instanceof BranchEmployee) {
			branchEmployeeMenu();
		}
		else if(currentUser instanceof Administrator) {
			adminMenu();
		}
		else
			throw new Exception("The given user object is not valid.");
	}
	
	/** Shows main menu for administrator operations */
	private void adminMenu() throws Exception {
		
		System.out.println("1- Add Branch");
		System.out.println("2- Remove Branch");
		System.out.println("3- Add Employee");
		System.out.println("4- Remove Employee");
		System.out.println("5- Product needs");
		System.out.println("6- Log out");

		String selection = getString("Enter selection");
		
		
		switch (selection) {
			case "1": addBranchMenu(); break;
			case "2": removeBranchMenu(); break;
			case "3": addEmployeeMenu(); break;
			case "4": removeEmployeeMenu(); break;
			case "5": productNeedsMenu(); break;
			case "6": logOut(); mainMenu(); break;
			default: System.out.println("Wrong selection please try again."); adminMenu();
		}			
	}
	
	/** Shows the menu for adding new branch employee */
	public void addEmployeeMenu() throws Exception {
		System.out.println("0- Back");
		String branchName = getString("Enter branch name to add employee");		

		if(branchName.equals("0"))
			turnMainMenu();
		else {

			try {
				repository.getBranchByName(branchName); 
				String name = getString("Enter branch employee name:");
				String surname = getString("Surname:");
				String mail = getString("E-mail:");
				String password = getString("Password:");
				BranchEmployee branchEmployee = new BranchEmployee(branchName, name, surname, mail, password);
			
				((Administrator)currentUser).addUser( branchEmployee );
				System.out.println("Branch employee added successfully");
				getString();
				turnMainMenu();
				}
				catch (Exception e) {
					System.out.println(e);
					addEmployeeMenu();
				}
			}
	}

	/** Shows the menu for remove a branch by name */
	public void removeBranchMenu() throws Exception {
		System.out.println(repository.getBranches());
		System.out.println("0- Back");
		String branchName = getString("Enter branch name to remove:");
		
		if(branchName.equals("0"))
			turnMainMenu();
		else {
			try {
					((Administrator)currentUser).removeBranch(branchName);
					System.out.println("Branch removed successfully");
					getString();
					turnMainMenu();
				}
				catch (Exception e) {
					System.out.println(e);
					removeBranchMenu();
				}
			}
	}

	/** Shows the menu product requirements by branch employees for administrator */
	public void productNeedsMenu() throws Exception {
		IContainer<Message> messages = ((Administrator)currentUser).getProductInforms();
		System.out.println(messages);
		if(messages.isEmpty())
			System.out.println("No product needs to show.");
		System.out.println("0- Back");
		getString("Enter anything to turn back main menu");
			turnMainMenu();
		
	}

	/** Shows the menu to remove branch employee for administrator */
	public void removeEmployeeMenu() throws Exception {
		System.out.println("0- Back");
		String branchEmployeeId = getString("Enter branch employee id to remove:");
		if(branchEmployeeId.equals("0"))
			turnMainMenu();
		else {
			
			try {
					User user =  repository.getEmployeeById(branchEmployeeId);
					((Administrator)currentUser).removeUser(user); 
					System.out.println("Branch employee removed successfully");
					getString();
					turnMainMenu();
				}
				catch (Exception e) {
					System.out.println(e);
					removeEmployeeMenu();
				}
			}
	}

	/** Shows the menu to add Branch for administrator*/
	public void addBranchMenu() throws Exception {
		System.out.println("0- Back");
		String branchName = getString("Enter new branch name:");
		
		if(branchName.equals("0"))
			turnMainMenu();
		
		else {
			((Administrator)currentUser).addBranch(branchName);
			System.out.println("Branch added successfully");
			getString();
			turnMainMenu();
		}
	}

	/** Shows the menu to remove product */
	public void removeProductMenu() throws Exception {
		listProducts(repository.getProducts());
		System.out.println("0- Turn main menu");
		String text = getString("Enter Id to remove:");
		if(text.equals("0"))
			turnMainMenu();
		else
		{
			Product product;
			try {
				product = repository.getProductById(text);
				repository.removeProduct(product);
				System.out.println("The product removed successfuly");
				removeProductMenu();
			} catch (Exception e) {
				System.out.println(e);
				removeProductMenu();
			}
			
		}
	}

	/** Shows the menu to add product */
	public void addProductMenu() throws Exception {
		
		Scanner scanner = new Scanner(System.in);
		System.out.println("1- BookCase");
		System.out.println("2- Chair");
		System.out.println("3- Meeting Table");
		System.out.println("4- Office Cabinet");
		System.out.println("5- Office Desk");
		
		Product product = null;
		int selection = scanner.nextInt();
		if(selection > 5 || selection < 1)
		{
				System.out.println("Wrong selection");
				addProductMenu();
				return;
		}
		System.out.println("Enter model name");
		String modelName = scanner.next();
		Color color = getColor();
		float price = 0.0f;
		try{
			price = Float.parseFloat(getString("Enter price:"));
		}catch(Exception e){
			System.out.println("Invalid Price");
			addProductMenu();
		}

		try {
			switch(selection) {
				case 1: product = new BookCase(modelName, color, price);break; 
				case 2: product = new Chair(modelName,color,price);break;
				case 3: product = new MeetingTable(modelName,color,price);break;
				case 4: product = new OfficeCabinet(modelName,color,price);break;
				case 5: product = new OfficeDesk(modelName,color,price);break; 
			}
			repository.addProduct(product);
		}
		
		catch (Exception e) { System.out.println(e); }
		System.out.println("Product is added");
		currentUserMenu();
	}
	

	/** To take value for the enum Color  */
	private Color getColor() {
		
		Scanner scanner = new Scanner(System.in);
		int selection;
		System.out.println("Select color:");
		
		int i=0;
		for (Color color : Color.values() ) {
			i++;
			System.out.println(i+"- "+color);
		}
		selection = scanner.nextInt();
		
		if(selection > Color.values().length || selection < 1)
			return getColor();
		else
			return Color.values()[selection-1];
	}

	/** Shows the menu for branch employee operations */
	private void branchEmployeeMenu() throws Exception {
		int selection;
		Scanner scanner = new Scanner(System.in);
		System.out.println("1- List products");
		System.out.println("2- Search product");
		System.out.println("3- Add product");
		System.out.println("4- Add product stock");
		System.out.println("5- Remove product");
		System.out.println("6- Make a sale");
		System.out.println("7- Get orders of a customer");
		System.out.println("8- Make Subscription a customer");
		System.out.println("9- Inform administrator about a product");
		System.out.println("10- Inquire product stock");
		System.out.println("11- Log out");

		selection = scanner.nextInt();
		
		switch (selection) {
			case 1: listProductMenu(); break;
			case 2: searchProductMenu(); break;
			case 3: addProductMenu(); break;
			case 4: addProductStockMenu(); break;
			case 5: removeProductMenu(); break;
			case 6: makeSaleMenu(); break;
			case 7: getOrderMenu(); break;
			case 8: makeSubscriptionMenu(); break;
			case 9: informAdminMenu(); break;
			case 10: inquireProductMenu(); break;
			case 11: currentUser = null; mainMenu(); break;
			default: System.out.println("Wrong selection please try again.");customerMenu();
		}		
	}

	/** Shows the menu to inquire a product by id */
	private void inquireProductMenu() throws Exception {
		System.out.println("0- Back");
		String productId = getString("Enter Product Id to Inquire :");
		
		if(productId.equals("0"))
			turnMainMenu();
		else {
			try{
				Product product = repository.getProductById(productId);
				System.out.println(product);
				turnMainMenu();
			}
			catch (Exception e) {
				System.out.println("The given product Id is not found.");
				inquireProductMenu();
			}
		}
	}


	/** Shows the menu to add new product (initializes stocks as 0)*/
	public void addProductStockMenu() throws Exception {
		System.out.println("0- Back");
		String productId = getString("Enter Product Id to add stock:");
		
		if(productId.equals("0"))
			turnMainMenu();
		else {
			try{
				Product product = repository.getProductById(productId);
				int size = Integer.parseInt( getString("Enter product size:") );
				((BranchEmployee)currentUser).addProductStock(product, size);
				getString();
				addProductStockMenu();
			}
			catch(NumberFormatException e) {
				System.out.println("Wrong integer format");
			}
			
			catch (Exception e) {
				System.out.println("The given product Id is not found.");
			}
		}
	}

	/** Shows the menu to inform administrator about a product with required amount*/
	public void informAdminMenu() throws Exception  {
		System.out.println("0- Back");
		String productId = getString("Enter Product Id:");
		
		if(productId.equals("0"))
			turnMainMenu();
		else {
			try{
				int requiredAmount = Integer.parseInt(getString("Required Amount:"));
				((BranchEmployee)currentUser).informAdmin(productId, requiredAmount);
				System.out.println("Message sent ");
				getString();
				turnMainMenu();
			}catch (NumberFormatException e) {
				System.out.println("Invalid amount try again!");
				informAdminMenu();
			}
		}
	}

	/** Shows the menu to subscript a customer */
	public void makeSubscriptionMenu() throws Exception {
		Employee employee = (Employee)currentUser;
		System.out.println("0- Back");
		String name = getString("Enter name:");
		if(name.equals("0"))
			turnMainMenu();
		else {
			String surname = getString("Enter Surname:");
			String mail = getString("Enter mail:");
			String password = getString("Enter password:");
			
			Customer customer = new Customer(name, surname, mail, password);
			employee.makeSubscription(customer);
			System.out.println("Subscription is completed successfully");
			getString();
			turnMainMenu();
		}
	}

	/** Shows the menu to get orders of a customer with customer id*/
	public void getOrderMenu() throws Exception {
		System.out.println("0- Back");
		String customerId = getString("Enter Customer Id to list orders:");
		if(customerId.equals("0") )
			turnMainMenu();
		else
		{	Employee employee = (Employee) currentUser;
			IContainer<Order> orders = employee.getOrdersOfCustomer(customerId);
			if( orders == null || orders.isEmpty()  )
				getString("There is no any Orders of the customer.\nEnter anything to turn back main menu");
			else
				System.out.println(orders);
			getString("Enter anything to turn back main menu");
			turnMainMenu();
		}
	}

	/** Shows the menu to make a sale */
	public void makeSaleMenu() throws Exception {
		
		BranchEmployee employee = (BranchEmployee) currentUser;
		listProducts(repository.getProducts());
		System.out.println("0- Turn Main Menu");
		String productId  = getString("Enter Prduct Id:");
		if(productId.equals("0"))
			turnMainMenu();
		else
		{	Product product = null;
			Customer customer = null;
			try{
				product = repository.getProductById(productId);
				System.out.println(repository.getCustomers());
				String customerId = getString("Enter Customer Id:");
				customer = repository.getCustomerById(customerId);
			}
			catch(Exception e){System.out.println(e);makeSaleMenu();}

			String phone = getString("Enter contact phone:");
			String address = getString("Enter address:");
			
			Order order = new Order( product,phone,address,customer);
		try{	employee.makeSale(order);}
		catch(Exception e){System.out.println(e+"\nInform Administrator");informAdminMenu();}
			getString("Sales is completed successfully");
			turnMainMenu();
		}
	}

	/** Shows the menu for Customer operations*/
	public  void customerMenu() throws Exception {
		
		System.out.println("1- List products");
		System.out.println("2- Search product");
		System.out.println("3- My orders");
		System.out.println("4- Order Product");
		System.out.println("5- Log out");
		String selection = getString("Selection:");
	
		switch (selection) {
			case "1": listProductMenu(); break;
			case "2": searchProductMenu(); break;
			case "3": ordersMenu(); break;
			case "4": orderProductMenu(); break;
			case "5": logOut(); mainMenu(); break;
			default: System.out.println("Wrong selection please try again.");customerMenu();
		}
		
	}
	
	/** Shows the menu to order a product for Customer */
	public void orderProductMenu() throws Exception {
		System.out.println("0- Back");
		String id = getString("Enter Product Id:");
		if(id.contentEquals("0"))
			turnMainMenu();
		else {
			try {
				Product product = repository.getProductById(id);
				String phone = getString("Enter contact phone:");
				String address = getString("Enter address:");
				Customer customer = ((Customer)currentUser);
				Order order = new Order( product,phone,address,customer);
				((Customer)currentUser).orderProduct(order);
				System.out.println("The order completed successfully");
				getString();
				turnMainMenu();
			}
			catch (Exception e) {
				System.out.println(e);
				orderProductMenu();
			}
		}
	}

	/** logs out the current user*/
	private void logOut() throws Exception {
		currentUser = null; 
	};

	/** Shows the orders of users or all orders according to current user */
	public void ordersMenu() throws Exception {
		IContainer<Order> orders = null;
		if(currentUser instanceof Customer)	{
			orders = ((Customer)currentUser).getMyOrders() ;
		}
		else if(currentUser instanceof BranchEmployee) {
			orders = repository.getOrders() ;		
		}
		else if(currentUser instanceof Administrator) {
			orders = repository.getOrders() ;
		}
		
		if(orders.isEmpty())
			System.out.println("There is no any orders to show");
		else
			System.out.println(orders);
		
		getString();
		turnMainMenu();
	}

	/** Shows the menu to search product with model name*/
	public void searchProductMenu() throws Exception {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Enter search text: ");
		String searchText = scanner.next();
		IContainer<Product> products = currentUser.searchProduct(searchText);
		
		if(products.size() > 0)
			listProducts(products);
		else
			System.out.println("Couldn't find any product with the given text.");
		 
		System.out.println("0-Search Again");
		String input = getString();
		if(input.contains("0"))
			searchProductMenu();
		else
			turnMainMenu();
	}
	
	/** Shows the menu to list all products */
	public void listProductMenu() throws Exception {
		listProducts(repository.getProducts());
		getString();
		turnMainMenu();
	}
	
	/** gets confirmation from the current user */
	private String getString() 
	{ 
		return getString("Enter anything to continue..."); 
	}
	
	/** gets a string from the current user */
	private String getString(String message)
	 { 
			Scanner scanner ;
			String text = new String();
	        System.out.println(message);
	        scanner = new Scanner(System.in);
	        try
	        {
	            text = scanner.nextLine();
	        }  
	        catch(Exception e)
	        {}
	        if(text.isBlank())
            	return getString();
			return text;
	        
	 }
	
	/** lists all products */
	private void listProducts(IContainer<Product> products) {

		Iterator<Product> it = products.iterator();
		
		Integer branchSize = repository.getBranches().size()*11; 
		
		
		String leftAlignFormat = "| %-5s | %-25s | %-10.2f | %-10s |" +  " %-"+ branchSize +"s |\n";
		
		System.out.println("+ "+ "-".repeat(5) +" + " + "-".repeat(25) +" + "+ "-".repeat(10)+" + "+ "-".repeat(10)+ " + " + "-".repeat(branchSize) +" +");

		System.out.format("| %-5s | %-25s | %-10s | %-10s |" +  " %-"+ branchSize +"s |\n"
					,"ID","MODEL NAME","PRICE","COLOR","STOCKS");
		System.out.println("+ "+ "-".repeat(5) +" + " + "-".repeat(25) +" + "+ "-".repeat(10)+" + "+ "-".repeat(10)+ " + " + "-".repeat(branchSize) +" +");
		
		
		while(it.hasNext()) {
			Product product = it.next();
			Iterator<Branch> branches = repository.getBranches().iterator();
			String stocks = new String();

			while(branches.hasNext())
				{
					Branch branch = branches.next();
					int stock = 0;
					try { stock = product.getStockInBranch(branch); } catch (Exception e) {}
					stocks += branch.getName() + ": " + stock +" ";
				}
				System.out.format(leftAlignFormat, product.getId(), product.getModelName(), product.getPrice(), product.getColor(), stocks);
		}
		System.out.println("+ "+ "-".repeat(5) +" + " + "-".repeat(25) +" + "+ "-".repeat(10)+" + "+ "-".repeat(10)+ " + " + "-".repeat(branchSize) +" +\n");

	}
	
	/** redirect the user to operation menu */
	private void turnMainMenu() throws Exception {
		if(currentUser instanceof Administrator) 
			adminMenu();
		
		else if(currentUser instanceof BranchEmployee) 
			branchEmployeeMenu();
			
		else if(currentUser instanceof Customer)	{
			customerMenu();
		}			
	}

	/** Shows the sign up menu */
	public User signUpMenu() throws Exception { 
		String name, surname , mail , password ;
		
		name = getString("Name: ");
		surname = getString("Surname: ");
		mail = getString("E-mail: ");
		password = getString("Password ");
		
		Customer newCustomer = new Customer(name, surname, mail, password);
		repository.addUser(newCustomer);
		System.out.println("Your id is: "+newCustomer.getId());
		return repository.login(mail, password);
	}

	/** Shows the login menu */
	public User loginMenu() throws Exception {
		System.out.println("0- Back");
		String email = new String(), password = new String();
		email = getString("E-mail: ");
		
		if(email.contentEquals("0"))
			{
				mainMenu();
				System.exit(1);
				return null;
			}
		else
		{	
			password = getString("Password: ");
			try {
				return repository.login(email, password);}
			catch (Exception e) { System.out.println(e); return loginMenu(); }
		}
	}
	
	

}
