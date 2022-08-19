import java.io.Serializable;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

/**
 * The class for the traders that extends User class
 */
public class Trader extends User {

    private Queue<Order> orders;
    private HashSet<Integer> productIds;

    /**
     * The constructor of the Trader class
     * @param name  the name of the trader
     * @param surname  the surname of the trader
     * @param password the password of the trader
     * @param phoneNumber the phone number of the trader
     */
    public Trader(String name, String surname, String password, String phoneNumber) {
        super(name, surname, password, phoneNumber);
        orders = new LinkedList<>();
        productIds = new HashSet<>();
    }

    /**
     * returns the product id's of the traders
     */
    public HashSet<Integer> getProductIds() {
        return productIds;
    }

    /**
     * Adds an product to the system
     * @param name the name of the product
     * @param description the description of the product
     * @param price the price of the product
     * @param discountedPrice the discounted Price of the product
     * @param category the category of the product
     * @return the added product
     * @throws Exception if the prices are not correct
     */
    public Product addProduct(String name, String description, float price, float discountedPrice, Category category) throws Exception {
        Product product = new Product(this.getId(),name, description, price, discountedPrice, category);
        ProductService.getInstance().add(product);
        productIds.add(product.getId());
        return product;
    }

    /**
     * removes the product with given product id
     * @param productId the id of the product
     * @return returns if the product is removed or not
     */
    public boolean removeProduct(Integer productId) throws Exception {
        if(productIds.remove(productId)) {
            ProductService.getInstance().remove(productId);
            return true;
        }
        return false;
    }

    /**
     * edits the product of trader
     * @param product the product to be edited
     * @throws Exception if the trader is not owner of the product
     */
    public void editProduct(Product product) throws Exception {
        if(productIds.contains(product.getId()))
            ProductService.getInstance().edit(product);
        else
            throw new Exception("The given product is not found to edit");
    }

    /**
     * returns the orders to the trader
     */
    public Queue<Order> getOrders(){
        return orders;
    }

    /**
     * sets the status of the product
     * @param order the order to be setted
     * @throws Exception if the order is not found
     */
    public void setStatusOfOrder(Order order, Order.OrderStatus orderStatus) throws Exception {
        if( ! orders.contains(order))
            throw new Exception("The trader do not have the given order to set order status.");
        else{
                order.setOrderStatus(orderStatus);
        }
    }


}
