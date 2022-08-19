import java.util.*;

/**
 * A customer class for the Project
 */
public class Customer extends User{

    Queue<Order> orders;

    /**
     * Constructor for the Customer class
     * @param name the name of the customer
     * @param surname the surname of the customer
     * @param password the password of the customer
     * @param phoneNumber the phone number of the customer
     */
    public Customer(String name, String surname, String password, String phoneNumber) {
        super(name, surname, password, phoneNumber);
        orders = new LinkedList<>();
    }

    /**
     * Searchs the searchText in products if the others not null then filters the results
     * @param serchText the text for the searching
     * @param category the category filter
     * @param priceDown price down filter
     * @param priceUp price up filter
     * @return the list of the results
     */
    public LinkedList<Product> searchOrQueryProduct(String serchText, Category category, Float priceDown, Float priceUp){
        return ProductService.getInstance().search(serchText,category,priceDown,priceUp);
    }

    /**
     * makes an order with given products
     * @param traderId the trader that owner of the products
     * @param productsAndSizes the products and sizes with hashMap
     * @throws Exception if the trader is not same or not correct
     */
    public void makeOrder(int traderId, HashMap<Product,Integer> productsAndSizes) throws Exception {
        for(Product product: productsAndSizes.keySet())
            if(product.getTraderId() != traderId)
                throw new Exception("Some of products have not same trader. Make another orders for from the other trades");

        Order order = new Order(traderId,this.getId(),productsAndSizes);
        orders.add(order);
        User user = UserService.getInstance().getUserById(traderId);
        if(user != null && user instanceof Trader){
            ((Trader) user).getOrders().add(order);
        }
        else
            throw new Exception("The given trader id is not correct please try again.");
    }

    /**
     * Returns all orders of the customer
     * @return Order queue
     */
    public Queue<Order> getOrders(){
        return orders;
    }

    /**
     * Return all products of an trader
     * @param traderId  the id of the trader
     * @return ArrayList of the products
     * @throws Exception if the trader id is not found
     */
    public ArrayList<Product> getAllProductsOfTrader(int traderId) throws Exception {
        return ProductService.getInstance().getAllProductsOfTrader(traderId);
    }

    /**
     * Sorts given products with bubble sort algorithm by price
     * @param products the products to be sorted
     */
    public void sortProductsByPrice(LinkedList<Product> products){
        BubbleSort bubbleSort = new BubbleSort();
        bubbleSort.sort(products, new Comparator<Product>() {
            @Override
            public int compare(Product o1, Product o2) {
                return o1.getDiscountedPrice().compareTo(o2.getDiscountedPrice());
            }
        });
    }

    /**
     * Sorts given products with shell sort algorithm by percentage of discount
     * @param products the products to be sorted
     */
    public void sortProductsByPercentOfDiscount(LinkedList<Product> products){
        ShellSort shellSort = new ShellSort();
        shellSort.sort(products, new Comparator<Product>() {
            @Override
            public int compare(Product o1, Product o2) {
                return o1.getPercentageOfDiscount().compareTo(o2.getPercentageOfDiscount());
            }
        });
    }

    /**
     * Sorts given products with merge sort algorithm by name
     * @param products the products to be sorted
     */
    public void sortProductsByName(LinkedList<Product> products){
        MergeSort mergeSort = new MergeSort();
        mergeSort.sort(products, new Comparator<Product>() {
            @Override
            public int compare(Product o1, Product o2) {
                return o1.getName().compareTo(o2.getName());
            }
        });
    }
}