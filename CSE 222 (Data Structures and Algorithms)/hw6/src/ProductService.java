import java.io.*;
import java.util.*;

/**
 * The class for productService
 * That includes all operations about products
 */
public class ProductService implements IProductService{

    private static ProductService productService1;
    private final static String directory = "products//";
    private Integer lastId;
    private static Category rootCategory;

    private ProductService(){
        getLastId();
        rootCategory = new Category("Product",null);
    }

    public static ProductService getInstance(){
        if(productService1 == null)
            productService1 = new ProductService();
        return productService1;
    }

    private void getLastId(){
        File folder = new File(directory);
        File[] listOfFiles = folder.listFiles();
        File max = null;
        if(listOfFiles != null && listOfFiles.length > 0) {
            max = listOfFiles[0];
            for (int i = 0; i < listOfFiles.length; i++) {
                if (Integer.parseInt((max.getName().split("\\.")[0])) < Integer.parseInt((listOfFiles[i].getName().split("\\.")[0])))
                    max = listOfFiles[i];
            }
            lastId = Integer.parseInt( max.getName().split("\\.")[0] );
        }

    }

    public int getNewId(){
        if(lastId == null)
            lastId = 0;
        else
            lastId++;

        return lastId;
    }


    @Override
    public void add(Product product) {
        product.setName(product.getName().toUpperCase());
        try {
            FileOutputStream fileOut = new FileOutputStream(directory+product.getId()+".txt");
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(product);
            objectOut.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public LinkedList<Product> search(String searchText, Category category, Float priceDown, Float priceUp) {
        searchText = searchText.toUpperCase();
        LinkedList<Product> products = new LinkedList<>();
        File folder = new File(directory);
        File[] listOfFiles = folder.listFiles();
        for (File productFile : listOfFiles) {
            int id = Integer.parseInt(productFile.getName().split("\\.")[0]);
            Product product = getProductById(id);

            if(category != null && ( category.getId() != product.getId() || !category.isDescendant(product.getCategoryName())))
                continue;
            if(priceDown != null && product.getDiscountedPrice() < priceDown)
                continue;
            if(priceUp != null && product.getDiscountedPrice() > priceUp)
                continue;
            if( product.getName().contains(searchText)
                    || product.getDescription().contains(searchText) )
                products.add(product);
        }
        return products;
    }

    @Override
    public void remove(int productId) throws Exception {
        File file = new File(directory+productId+".txt");
        if( ! file.delete())
            throw new Exception("The product is not found to delete");
    }

    @Override
    public void edit(Product product) throws Exception {
        try {
            remove(product.getId());
            add(product);
        } catch (Exception e) {
            throw new Exception("The product is not found to edit");
        }
    }

    @Override
    public ArrayList<Product> getAllProductsOfTrader(int traderId) throws Exception {
        UserService userService = UserService.getInstance();
        Trader trader;
        User user = userService.getUserById(traderId);
        if (user != null && user instanceof Trader)
            trader = (Trader) user;
        else
            throw new Exception("The Trader not found");

        ArrayList<Product> products = new ArrayList<>();
        for(Integer id: trader.getProductIds())
            products.add(getProductById(id));
        return products;
    }

    @Override
    public Product getProductById(Integer productId) {
        Product product = null;
        try {
            FileInputStream fileIn = new FileInputStream(directory+productId+".txt");
            ObjectInputStream in = new ObjectInputStream(fileIn);
            product = (Product) in.readObject();
            in.close();
            fileIn.close();
        } catch (IOException e) {
            return null;
        } catch (ClassNotFoundException c) {
            System.out.println("Product class not found");
            c.printStackTrace();
        }
        return product;
    }

    public void fetchFromCSV(String fileName) {    // we don't make any changes
        try {
            CsvReader csvReader = new CsvReader("e-commerce-samples.csv");

            ArrayList<Product> products = new ArrayList<>();
            String[] line = csvReader.getLine();
            HashMap<String, Trader> traders = new HashMap<>();
            Trader trader = null;
            while (line != null){
                if(!traders.containsKey(line[5])) {
                    trader = new Trader(line[5], " ", "123456", "+90111111111");
                    traders.put(line[5],trader);
                    UserService.getInstance().addUser(trader);
                }

                Category category = rootCategory.addCategoryHierarchy(line[1]);
                Product product = new Product(trader.getId(),line[0],line[4],Float.parseFloat(line[2]),Float.parseFloat(line[3]),category);
                products.add(product);
                line = csvReader.getLine();
            }
            UserService.getInstance().saveUsers();
            rootCategory.save();
            for (Product product:products)
                productService1.add(product);

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }







    public static void main(String args[]) {                     // Tests

        try {
            Product product = new Product(10000000,"Table5","Circular big table",200,20,new Category("Home",null));
            ProductService productService = new ProductService();
         /*   productService.add(product);
            product = productService.getProductById(0);
            System.out.println(product.getName() + product.getPrice() +" " + productService.getNewId());


            product.setPrice(500);
            productService.edit(product);

            System.out.println(product.getName() + product.getPrice() +" " + productService.getNewId());
*/
            ArrayList<Product> products = new ArrayList<>();
            productService.fetchFromCSV("e-commerce-samples.csv");

            System.out.println(products.get(0).getName()+products.get(0).getPrice()+products.get(0).getDescription()+products.get(0).getCategoryName());
            for(Product product1 : products)
                productService.add(product1);

            rootCategory.save();
            System.out.println(products.get(0).getName()+products.get(0).getPrice()+products.get(0).getDescription()+products.get(0).getCategoryName());

            LinkedList<Product> searchResults = productService.search("ipad",null,null,null);
            System.out.println(searchResults.size());
            for (Product product1 : searchResults)
                System.out.println(product1.getName());

            searchResults = productService.search("ipad",null,500.0f,1000.0f);
            System.out.println(searchResults.size());
            for (Product product1 : searchResults)
                System.out.println(product1.getName() +" " +product1.getPrice());




        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
