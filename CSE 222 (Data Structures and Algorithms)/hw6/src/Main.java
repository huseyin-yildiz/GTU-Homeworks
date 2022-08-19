import java.util.*;

public class Main {

    public static void main(String[] args){
        UserService userService = UserService.getInstance();
        Trader trader = new Trader("Test","test","123456","+905555555555");
        userService.addUser(trader);
        System.out.println(userService.getUserById(trader.getId()).getName() +" "+ trader.getSurname());

        try {
            trader = (Trader) userService.login(trader.getId(),"132456");        // gives error
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            trader = (Trader) userService.login(trader.getId(),"123456");
            System.out.println(trader);
        } catch (Exception e) {
            e.printStackTrace();
        }


        userService.removeUser(trader.getId());
        System.out.println(userService.getUserById(trader.getId()));        // removing user


        ProductService productService = ProductService.getInstance();

        if(productService.getNewId() < 10000)
            productService.fetchFromCSV("e-commerce-samples.csv");

        userService.addUser(trader);
        trader = (Trader) userService.getUserById(trader.getId());
        System.out.println(trader);

        try {
            Category rootCategory = Category.load();
            Category testCategory = new Category("testCategory",rootCategory);
            rootCategory.addChild(testCategory);
            Product testProduct = trader.addProduct("test product","test-test",1000.0f,800f,testCategory);

            testProduct.setDiscountedPrice(500);
            trader.editProduct(testProduct);
            System.out.println(productService.getProductById(testProduct.getId()));

            trader.removeProduct(testProduct.getId());
            System.out.println(productService.getProductById(testProduct.getId()));

            trader.removeProduct(-5);

            Product testProduct2 = trader.addProduct("test product2","test-test2",1080.0f,750f,testCategory);

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }


        // Customer tests


        Customer customer = new Customer("Customer","Test","123456","+950000000000");

        LinkedList<Product> searchResults = customer.searchOrQueryProduct("ipad",null,null,null);
        for (Product product: searchResults)
            System.out.println(product);

        System.out.println("\n\n-----------------\n");

        searchResults = customer.searchOrQueryProduct("ipad",null,600f,900f);
        for (Product product: searchResults)
            System.out.println(product);


        customer.sortProductsByName(searchResults);
        System.out.println("\n\n--------------sort search results by name--------------");
        for (Product product: searchResults)
            System.out.println(product);

        customer.sortProductsByPrice(searchResults);
        System.out.println("\n\n--------------sort search results by price--------------");
        for (Product product: searchResults)
            System.out.println(product);

        customer.sortProductsByPercentOfDiscount(searchResults);
        System.out.println("\n\n--------------sort search results by percentage of discount--------------");
        for (Product product: searchResults)
            System.out.println(product);

        ArrayList<Product> productsOfTrader = null;
        try {
            System.out.println("\n\n------------- All Products Of Trader -------------");
            productsOfTrader = customer.getAllProductsOfTrader(trader.getId());
            for (Product product : productsOfTrader)
                System.out.println(product);

            System.out.println("\n\n------------- All Products with Wrong Trader Id -------------");
            productsOfTrader = customer.getAllProductsOfTrader(-55);
            for (Product product : productsOfTrader)
                System.out.println(product);

        }catch (Exception e){
            System.out.println(e.getMessage());
        }

        try {
            // Order test


            System.out.println("\n\n------------- Making an order -------------");
            HashMap<Product,Integer> productsToOrder = new HashMap<>();
            productsToOrder.put(productsOfTrader.get(0),5);
            customer.makeOrder(trader.getId(),productsToOrder);


            System.out.println("\n\n------------- listing orders -------------");
            Queue<Order> ordersOfTrader = trader.getOrders();
            for (Order order: ordersOfTrader)
                System.out.println(order);


            System.out.println("\n\n------------- accept order -------------");
            customer.getOrders().peek().setOrderStatus(Order.OrderStatus.Accepted);
            ordersOfTrader = trader.getOrders();
            for (Order order: ordersOfTrader)
                System.out.println(order);


            System.out.println("\n\n------------- cancel order -------------");
            customer.getOrders().peek().setOrderStatus(Order.OrderStatus.Cancelled);
            ordersOfTrader = trader.getOrders();
            for (Order order: ordersOfTrader)
                System.out.println(order);

            System.out.println("\n\n------------- Making order with wrong trader-------------");
            customer.makeOrder(-55,productsToOrder);


        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println("-----------Category tree test-----------");
        Category category = new Category("TestCategory",null);
        category.addChild(new Category("subCategory1",category));
        category.addChild(new Category("subCategory2",category));
        System.out.println(category.getChildren().get("subCategory1").getParent().getName());
        Category category3 = new Category("subCategory3",category.getChildren().get("subCategory1"));
        category.getChildren().get("subCategory1").addChild(category3);

        System.out.println(category.isDescendant(category3.getName()));
        System.out.println(category3.isDescendant(category.getName()));

        category3.addCategoryHierarchy("[\"Clothing >> Kids' Clothing >> Girls Wear >> Dresses & Skirts >> Dresses >> Kids On Board Dresses\"]");


    }


}
