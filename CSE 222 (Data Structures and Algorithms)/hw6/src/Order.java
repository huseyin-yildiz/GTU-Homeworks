import java.util.HashMap;
import java.util.Map;

/**
 * The order class for the orders
 */
public class Order implements Identifiable{

    /**
     * The order status enum for status of the orders
     */
    public static enum OrderStatus{
        Accepted,
        Cancelled,
        Waiting,
        Delivered
    }

    /**
     * Holds products and amount of them
     * */
    private HashMap<Product,Integer> products;
    private OrderStatus orderStatus;
    private int traderId;
    private int customerId;


    /**
     * The constructor for the order
     * @param traderId  the id of the trader
     * @param customerId the id of the customer that make order
     * @param products the products to be ordered
     */
    public Order(int traderId, int customerId, HashMap<Product,Integer> products) {
        this.traderId = traderId;
        this.customerId = customerId;
        this.products = products;
        orderStatus = OrderStatus.Waiting;
    }


    /**
     * returns the status of the order
     * @return orderStatus enum
     */
    public OrderStatus getOrderStatus() {
        return orderStatus;
    }

    /**
     * sets the orderStatus
     * @param orderStatus OrderStatus enum
     */
    public void setOrderStatus(OrderStatus orderStatus) {
        this.orderStatus = orderStatus;
    }


    /**
     * adds the product to the order
     * @param product product to be added to the order
     * @param amount the amount of the product
     * @throws Exception if the product is not from the same trader
     */
    public void addProduct(Product product, int amount) throws Exception {

        if(product.getTraderId() != traderId)
            throw new Exception("The trader must be same to order. You should make new order");

        if(products.containsKey(product) ) {
            int oldAmount = products.get(product);
            products.put(product,oldAmount+amount);
        }
        else {
            if(products.isEmpty())
                traderId = product.getTraderId();
            products.put(product, amount);
        }
    }

    /**
     * returns the id of the order
     */
    @Override
    public Integer getId() {
        return 0;
    }

    /**
     * compare to method for orders
     */
    @Override
    public int compareTo(Object o) {
        Order other = ((Order) o);
        return getId().compareTo(other.getId());
    }

    /**
     * converts the order object to the string text
     * @return String about the order
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Products:[");
        for (Map.Entry<Product,Integer> entry: products.entrySet())
            sb.append(entry.getKey().getName()+"-amount:"+entry.getValue()+"|");
        sb.append("] OrderStatus:");
        sb.append(orderStatus);
        return sb.toString();
    }
}
