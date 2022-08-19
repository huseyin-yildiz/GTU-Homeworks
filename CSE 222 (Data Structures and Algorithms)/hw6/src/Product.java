import java.io.Serializable;

/**
 * The product class for the products
 */
public class Product implements Identifiable, Serializable {

    private int id;
    private String description;
    private String name;
    private float price;
    private float discountedPrice;
    private int traderId;
    private String categoryName;

    /**
     * The constructor that initializes the product instance
     * @param traderId the id of the trader that owner of the product
     * @param name the name of the product
     * @param description   the description of the product
     * @param price the price of the product
     * @param discountedPrice the discounted of the product
     * @param category the category of the product
     * @throws Exception if the discountedPrice and price is not correct.
     */
    public Product(int traderId, String name, String description, float price, float discountedPrice, Category category) throws Exception {
            if(discountedPrice > price)
                throw new Exception("The discount can not be larger than the price");
            if(discountedPrice < 0)
                throw new Exception("The discount can not be negative number");
            if(price < 0)
                throw new Exception("The price can not be negative number");
            else{
                ProductService productService = ProductService.getInstance();
                id = productService.getNewId();
                this.traderId = traderId;
                this.categoryName = category.getName();
                this.description = description;
                this.discountedPrice = discountedPrice;
                this.price = price;
                this.name = name;
            }
    }

    /**
     * returns the name of the product
     */
    public String getName() {
        return name;
    }

    /**
     * sets the name of the product
     * @param name the name to be set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * returns the id of the owner of the product
     * @return
     */
    public int getTraderId() {
        return traderId;
    }

    /**
     * returns the name of the category
     * @return
     */
    public String getCategoryName() {
        return categoryName;
    }

    /**
     * sets the category of the product
     * @param category category of the product to be set
     */
    public void setCategory(Category category) {
        this.categoryName = category.getName();
    }

    /**
     * returns the description of the product
     */
    public String getDescription() {
        return description;
    }

    /**
     * sets the description of the product
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * returns the price of the product
     */
    public Float getPrice() {
        return price;
    }

    /**
     * sets the price of the product
     */
    public void setPrice(float price) {
        this.price = price;
    }

    /**
     * returns the discounter price of the product
     */
    public Float getDiscountedPrice() {
        return discountedPrice;
    }

    /**
     * sets the discounted price of the product
     */
    public void setDiscountedPrice(float discountedPrice) {
        this.discountedPrice = discountedPrice;
    }

    /**
     * returns the percentage of the discount
     */
    public Float getPercentageOfDiscount(){
        return discountedPrice / price;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public int compareTo(Object o) {
        Product other = ((Product) o);
        return getId().compareTo(other.getId());
    }

    @Override
    public String toString() {
        return "name:"+name +" price:"+price+" discountedPrice:"+discountedPrice+" category:"+categoryName;
    }
}
