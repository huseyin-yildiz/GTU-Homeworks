import java.util.Scanner;

import Containers.IContainer;
import Containers.MyList;

public class Main {

	
	static MyRepository repository;
	static User currentUser;
	
	/** The driver method */
	public static void main(String[] args) {
		
		try {
			if(args.length > 0)
				System.out.println(args[0]);
			else
			{
				repository = MyRepository.getInstance();
				loadSystem();
			}
			Scanner scanner = new Scanner(System.in);
			String text;
		
			System.out.println("1- Unit Test");
			System.out.println("2- Interactive User Menu");
			text = scanner.next();
			if(text.equals("1"))
				test();
			else if(text.equals("2"))
				new ConsoleMenu().mainMenu();
			else
				main(new String[] {"wrong selection"});

		}		

		catch (Exception e) {
			//System.out.println(e);
			e.printStackTrace();
		}
	}

	/** The method to test the system */
	private static void test() throws Exception  {
		// admin
		Administrator admin = new Administrator("admin", "test", "admin@test.com", "12345678");
		repository.addUser(admin);
		System.out.println( repository.getAdministrators() );
		
			// branches
		admin.addBranch("branch3");
		admin.addBranch("branch4");
		System.out.println( repository.getBranches().toString("-") );
		admin.removeBranch("branch3");
		
		System.out.println( repository.getBranches().toString("-") );
		
			// employees
		BranchEmployee employee1 = new BranchEmployee("branch4","mehmet", "yılmaz", "qwer@asd.com", "q12345"); 
		admin.addUser(employee1);
		BranchEmployee employee2 = new BranchEmployee("branch4","ahmet", "yılmaz", "aqwr@asd.com", "a345431"); 
		admin.addUser(employee2);
		
		Branch branch2 = repository.getBranchByName("branch4");
		System.out.println(branch2.getEmployees());
		admin.removeUser(employee1);
		System.out.println(branch2.getEmployees());
		
		
		//products
		BookCase chair1 = new BookCase ("Chair model-15",Color.purple,265.4f);
		employee2.removeProduct(chair1);
		employee2.addProduct(chair1, 20);
		MeetingTable  meetingTable1 = new MeetingTable("Meeting Table model-1",Color.gray,295.8f);
		employee2.addProduct(meetingTable1, 50);
		OfficeCabinet officeCabinet1 = new OfficeCabinet("Office Cabinet model-3",Color.black,405.4f);
		employee2.addProduct(officeCabinet1, 20);
		System.out.println(repository.getProducts().toString("\n"));
		employee2.removeProduct(meetingTable1);
		System.out.println(repository.getProducts().toString("\n"));
		
		//subscription
		Customer customer1 = new Customer("veli", "şeker", "veli@test.com", "v12345678");
		employee2.makeSubscription(customer1);
		System.out.println(repository.getCustomers());
		
		//orders
		IContainer<Product> productsToOrder = new MyList<Product>();
		productsToOrder.add(chair1);
		productsToOrder.add(officeCabinet1);
		Order order1 = new Order(productsToOrder, "+905555555", "gebze, kocaeli",customer1 );
		employee2.makeSale(order1);
		System.out.println(employee2.getOrdersOfCustomer( customer1.getId()) );
		
		// stock
		System.out.println(employee2.getStockOfProduct(chair1) );
		
		
		//customer
		Customer customer3 = new Customer("Ali","Demir","ali@test.com","pass1234");
		repository.addUser(customer3);
		System.out.println( "List Of Products: " + customer1.getProducts().toString("\n") );
		IContainer<Product> searching = customer3.searchProduct("Chair");
		System.out.println("Found " +searching.size() +" product: \n" + searching.toString("\n"));
		
		IContainer<Product> myProductsToOrder = new MyList<Product>();
		myProductsToOrder.add(chair1);
		customer3.orderProduct(myProductsToOrder,"+999999999","Istanbul");
		System.out.println("myOrders: "+ customer3.getMyOrders());
		employee2.informAdmin("3", 22);
		
		//Customer
	//	ConsoleMenu consoleMenu = new ConsoleMenu();
	//	consoleMenu.currentUser = repository.login("ali@test.com", "pass1234"); 
	//	consoleMenu.currentUserMenu();
	//	consoleMenu.listProducts(repository.getProducts());
	//	consoleMenu.logOut();
		
		// Branch Employee
	//	consoleMenu.currentUser = repository.login( "aqwr@asd.com", "a345431");
	//	consoleMenu.branchEmployeeMenu();
	//	consoleMenu.searchProductMenu();
	//	Color clr = consoleMenu.getColor();
	//	System.out.println(clr);
		
	//	consoleMenu.addProductMenu();
		
	//	consoleMenu.removeProductMenu();
	//	consoleMenu.makeSaleMenu();
	//	consoleMenu.getOrderMenu();
		
	//	consoleMenu.makeSubscriptionMenu();
	//	consoleMenu.informAdminMenu();
		
	//	consoleMenu.logOut();
		
		
		//Administrator Menu
	//	consoleMenu.currentUser = repository.login("admin@test.com", "12345678");
	//	consoleMenu.addBranchMenu();
	//	consoleMenu.removeBranchMenu();
	//	consoleMenu.addEmployeeMenu();
	//	System.out.println(repository.getBranchByName("branch2").getEmployees()) ;
		
	//	System.out.println(repository.getBranchByName("branch2").getEmployees()) ;
		
	//	consoleMenu.removeEmployeeMenu();
	//	System.out.println(repository.getBranchByName("branch2").getEmployees()) ;
	
	//	consoleMenu.productNeedsMenu();
	//	consoleMenu.logOut();
	//	consoleMenu.mainMenu();
	
	}
	
	/** adds some users,branches, employees, products to repository of system  */
	public static void loadSystem() throws Exception {
		
		// adding administrator
		Administrator admin = new Administrator("admin", "test", "admin@test.com", "12345678");
		repository.addUser(admin);
		
		//adding branches
		admin.addBranch("branch1");
		admin.addBranch("branch2");
		
		// adding branchEmployees
		BranchEmployee employee1 = new BranchEmployee("branch1","mehmet", "yılmaz", "qwer@asd.com", "q12345"); 
		admin.addUser(employee1);
		BranchEmployee branchEmployee = new BranchEmployee("branch2","ahmet", "yılmaz", "aqwr@asd.com", "a345431"); 
		admin.addUser(branchEmployee);
		
		
		IContainer<Color> colors = new MyList<Color>();
		colors.add(Color.black);
		colors.add(Color.blue);
		colors.add(Color.red);
		colors.add(Color.green);
		
		// adding office desks 
		branchEmployee.addProducts (new OfficeDesk("OfficeDesk model-1", 450.2f),colors);
		branchEmployee.addProducts (new OfficeDesk("OfficeDesk model-2", 460.9f),colors);
		branchEmployee.addProducts (new OfficeDesk("OfficeDesk model-3", 480.4f),colors);
		branchEmployee.addProducts (new OfficeDesk("OfficeDesk model-4", 350.9f),colors);
		branchEmployee.addProducts (new OfficeDesk("OfficeDesk model-5", 540.5f),colors);
		
		//adding meeting tables
		branchEmployee.addProducts (new MeetingTable("Meeting table model-1",  740.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-2", 770.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-3", 710.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-4", 640.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-5", 840.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-6", 940.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-7", 590.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-8", 610.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-9", 647.5f),colors);
		branchEmployee.addProducts (new MeetingTable("Meeting table model-10", 835.5f),colors);
		
		
		//adding bookcases
		branchEmployee.addProduct (new BookCase("Bookcase model-1", Color.blue, 435.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-2", Color.gray, 560.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-3", Color.black, 458.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-4", Color.red, 421.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-5", Color.white, 475.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-6", Color.orange, 497.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-7", Color.green, 410.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-8", Color.gray, 416.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-9", Color.purple, 475.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-10", Color.purple, 445.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-11", Color.white, 485.5f));
		branchEmployee.addProduct (new BookCase("Bookcase model-12", Color.gray, 535.5f));
		
		//adding Office Cabinets
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-1", Color.gray, 635.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-2", Color.blue, 645.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-3", Color.black, 695.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-4", Color.white, 457.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-5", Color.red, 567.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-6", Color.orange, 624.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-7", Color.green, 395.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-8", Color.purple, 759.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-9", Color.white, 632.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-10", Color.gray, 723.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-11", Color.green, 453.5f));
		branchEmployee.addProduct (new OfficeCabinet("Bookcase model-12", Color.black, 535.5f));
		
		//adding Chairs
		colors.add(Color.white);
		branchEmployee.addProducts (new Chair("Chair model-1", 235.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-2", 285.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-3", 205.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-4", 215.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-5", 315.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-6", 353.5f),colors);
		branchEmployee.addProducts (new Chair("Chair model-7", 405.5f),colors);
		
		
	}
	
	

}
