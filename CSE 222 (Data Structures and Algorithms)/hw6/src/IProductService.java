import java.util.ArrayList;
import java.util.LinkedList;

/**
 * The interface for productService
 * That includes all operations about products
 */
public interface IProductService {

    public void add(Product product);
    public LinkedList<Product> search(String searchText, Category category, Float priceDown, Float priceUp);
    public void remove(int productId) throws Exception;
    public void edit(Product product) throws Exception;
    public ArrayList<Product> getAllProductsOfTrader(int traderId) throws Exception;
    public Product getProductById(Integer productId);


}
