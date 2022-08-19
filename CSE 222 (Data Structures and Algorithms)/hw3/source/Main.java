import java.util.ListIterator;
import java.util.Scanner;

import Containers.HybridList;
import Containers.IContainer;
import Containers.KWArrayList;

public class Main {
	
	static MyRepository repository;
	static User currentUser;
	
	/** The driver method */
	public static void main(String[] args) {						// since this part is for testing i didnt analysed
		
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
		IContainer<Product> productsToOrder = new KWArrayList<Product>();
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
		
		IContainer<Product> myProductsToOrder = new KWArrayList<Product>();
		myProductsToOrder.add(chair1);
		customer3.orderProduct(myProductsToOrder,"+999999999","Istanbul");
		System.out.println("myOrders: "+ customer3.getMyOrders());
		employee2.informAdmin("3", 22);
		

		listsTest();
		
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
		
		
		IContainer<Color> colors = new KWArrayList<Color>();
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
	
	
	private static void listsTest() {
		
		System.out.println( "\n--------------HybridList---------------- \n");
		
		HybridList<String> a = new HybridList<String>();
		a.add("ali");
		a.add(0, "qwertyyuu");										//
		ListIterator<String> it = a.listIterator(0);
		System.out.println(it.hasNext());
		System.out.println(it.next());
		it.add("veli");
		it = a.listIterator();
		it.next();
		System.out.println("next1 "+ it.next());
		System.out.println( a );
		
		System.out.println(it.previous());
		System.out.println( a );
		
		System.out.println( it.nextIndex() );
		System.out.println("1: "+ a );
		
		it.add("zeki");
		System.out.println("2: "+ a);
		
		System.out.println(a.contains("zeki"));
		a.remove("zeki");
		System.out.println(a.contains("zeki"));
		a.clear();
		a.add("asd");
		System.out.println(a);
		a.add("qwe");
		a.add("qwqwase");
		
		System.out.println( a.isEmpty());
		
		System.out.println(a);
		System.out.println( a.indexOf("asd") );
		System.out.println( a.indexOf("qwe") );
		System.out.println( a.indexOf("qwqwase") );
		a.add("ccccc");												//
		a.add(2, "qwertyyuu");										//
		System.out.println(a);
		
		a.remove("qwqwase");									//
		System.out.println( a.indexOf("qwqwase") );				//
		
		a.remove(1);
		
		try {
		a.remove(2500);									//
		}catch(Exception e)
		{
			System.out.println(e);
		}
		
		System.out.println(a);
		

System.out.println( "\n--------------KWLinkedList---------------- \n");
		
		HybridList<String> b = new HybridList<String>();
		b.add("ali");
		b.add(0, "qwertyyuu");										
		b.add(b.size(),"asdddf");							// adding tail
		it = b.listIterator(0);
		System.out.println(it.hasNext());
		System.out.println(it.next());
		it.add("veli");
		it = b.listIterator();
		it.next();
		System.out.println("next1 "+ it.next());
		System.out.println( b );
		
		System.out.println(it.previous());
		System.out.println( b );
		
		System.out.println( it.nextIndex() );
		System.out.println("1: "+ b );
		
		it.add("zeki");
		System.out.println("2: "+ b);
		
		System.out.println(b.contains("zeki"));
		b.remove("zeki");
		System.out.println(b.contains("zeki"));
		b.clear();
		b.add("asd");
		System.out.println(b);
		b.add("qwe");
		b.add("qwqwase");
		
		System.out.println( b.isEmpty());
		
		System.out.println(b);
		System.out.println( b.indexOf("asd") );
		System.out.println( b.indexOf("qwe") );
		System.out.println( b.indexOf("qwqwase") );
		
		b.remove(1);
		System.out.println(b);
		
		b.add("ccccc");												
		b.add(2, "qwertyyuu");										
		System.out.println(b);
		
		b.remove("qwqwase");									
		System.out.println( b.indexOf("qwqwase") );				
		
		b.remove(1);
		
		try {
		b.remove(2500);									
		}catch(Exception e)
		{
			System.out.println(e);
		}
		
		System.out.println(b);
		
		
		
System.out.println( "\n--------------KWArrayList---------------- \n");
		
		HybridList<String> c = new HybridList<String>();
		c.add("ali");

		c.add(0, "qwertyyuu");										
		c.add(c.size(),"asdddf");							// adding tail
		
		it = c.listIterator(0);
		System.out.println(it.hasNext());
		System.out.println(it.next());
		it.add("veli");
		it = c.listIterator();
		it.next();
		System.out.println("next1 "+ it.next());
		System.out.println( c );
		
		System.out.println(it.previous());
		System.out.println( c );
		
		System.out.println( it.nextIndex() );
		System.out.println("1: "+ c );
		
		it.add("zeki");
		System.out.println("2: "+ c);
		
		System.out.println(c.contains("zeki"));
		c.remove("zeki");
		System.out.println(c.contains("zeki"));
		c.clear();
		c.add("asd");
		System.out.println(c);
		c.add("qwe");
		c.add("qwqwase");
		
		System.out.println( c.isEmpty());
		
		System.out.println(c);
		System.out.println( c.indexOf("asd") );
		System.out.println( c.indexOf("qwe") );
		System.out.println( c.indexOf("qwqwase") );
		
		c.remove(1);
		System.out.println(c);
		
		c.add("ccccc");												
		c.add(2, "qwertyyuu");										
		System.out.println(c);
		
		c.remove("qwqwase");									
		System.out.println( c.indexOf("qwqwase") );				
		
		c.remove(1);
		
		try {
		c.remove(2500);									
		}catch(Exception e)
		{
			System.out.println(e);
		}
		
		System.out.println(c);
		
		
	}
	
	

}
