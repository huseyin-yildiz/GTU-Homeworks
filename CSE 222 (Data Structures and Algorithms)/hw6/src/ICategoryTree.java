import java.util.HashMap;
import java.util.List;

/**
 * The CategoryTree interface for the hierarchic categories
 */
public interface ICategoryTree {
    /**
     * Returns name of the category
     * @return name of the category
     */
    String getName();

    /**
     * returns the parent of the category
     * @return parent category
     */
    Category getParent();

    /**
     * returns the sibligs of the category
     * @return the hashmap of the categories
     */
    HashMap<String, Category> getSiblings();

    /**
     * returns the children of the category
     * @return Hashmap of the children
     */
    HashMap<String, Category> getChildren();

    /**
     * returns the descendants of the category
     */
    HashMap<String, Category> getDescendants();

    /**
     * adds child to the category node
     */
    void addChild(Category category);

    /**
     * adds children to the category node
     */
    void addChildren(HashMap<String,Category> categories);

    /**
     * returns if the given category is descendant or not
     * @param categoryName the category to test if its descendant
     * @return boolean value
     */
    boolean isDescendant(String categoryName);

    /**
     * adds the hiearchy string to the category node
     * @param hierarchy
     * @return
     */
    Category addCategoryHierarchy(String hierarchy);
}
