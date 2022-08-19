import java.io.*;
import java.util.*;
/**
 * The category classs for the project
 */
public class Category implements Identifiable, Serializable,ICategoryTree {

    private int id;
    private String name;
    private Category parent;
    private HashMap<String,Category> children;
    private final static String savePath = "categories.txt";

    /**
     * Constructor of the category class
     * @param name Category name
     * @param parent The parent of the category
     */
    public Category(String name, Category parent){
        this.name = name;
        this.parent = parent;
        this.children = new HashMap();
    }

    /**
     * Returns id of the category
     */
    @Override
    public Integer getId() {
        return id;
    }

    /**
     * compares with another category if its same or not by id
     */
    @Override
    public int compareTo(Object o) {
            Category other = ((Category) o);
            return getId().compareTo(other.getId());
    }

    /**
     * sets the name of the category
     * @param name The name of the category
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Returns name of the category
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * Returns parent of the category
     */
    @Override
    public Category getParent() {
        return parent;
    }

    /**
     * Returns sibligs of the category if has
     */
    @Override
    public HashMap<String, Category> getSiblings() {
        HashMap<String,Category> sibligs = new HashMap<String,Category>(parent.getChildren());
        sibligs.remove(this.name);
        return  sibligs;
    }

    /**
     * Returns children of the category if it has
     */
    @Override
    public HashMap<String, Category> getChildren() {
        return children;
    }

    /**
     * Returns descendants of the category if it has
     */
    @Override
    public HashMap<String, Category> getDescendants() {
        HashMap<String,Category> descendants = new HashMap<String,Category>(children);
        for(Category category1: children.values()){
            descendants.putAll(category1.getDescendants());
        }
        return descendants;
    }

    /**
     * adds a child category to the category
     * @param category the child category
     */
    @Override
    public void addChild(Category category) {
        children.put(category.name, category);
    }

    /**
     * adds all categories as children
     * @param categories all categories to be children
     */
    @Override
    public void addChildren(HashMap<String,Category> categories) {
        children.putAll(categories);
    }

    /**
     * Returns if the param is descendant or not
     * @param categoryName the categoryName to search for descendant
     */
    @Override
    public boolean isDescendant(String categoryName) {
        if(children.containsKey(categoryName))
            return true;
        else
            for(String childName: children.keySet()){
                if(isDescendant(childName))
                    return true;
            }
        return false;
    }

    /**
     * takes an string hierarchy and adds them one by one
     * @param hierarchy a string like ["fruits >> apple"]
     */
    @Override
    public Category addCategoryHierarchy(String hierarchy) {
        if(hierarchy.startsWith("[\""))
            hierarchy = hierarchy.substring(2,hierarchy.length()-2);
        ArrayList<String> categoryNames = new ArrayList<>();
        Collections.addAll(categoryNames,hierarchy.split(" >> "));
        return addCategoryHierarchy(categoryNames,0);
    }

    /**
     * helper recursive function of the public method addCategoryHierarchy
     */
    private Category addCategoryHierarchy(List<String> categories,int index){
            if(index == categories.size()-1) {
                if(! children.containsKey(categories.get(index)))
                    addChild(new Category(categories.get(index),this));
                return children.get(categories.get(index));
            }
            else {
                String name = categories.get(index);
                if (!children.containsKey(name))
                    addChild(new Category(categories.get(index),this));
                return children.get(name).addCategoryHierarchy(categories,index+1);
            }
    }

    /**
     * saves the category trees to the file
     */
    public void save(){
        try {
            FileOutputStream fileOut = new FileOutputStream(savePath);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(this);
            objectOut.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * loads the category tree from the file
     */
    public static Category load() throws Exception {
        try {
            FileInputStream fileIn = new FileInputStream(savePath);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            Category category = (Category) in.readObject();

            in.close();
            fileIn.close();

            return category;
        } catch (IOException e) {
            throw new Exception("The file not found");
        } catch (ClassNotFoundException c) {
            throw new Exception("Category class not found.");
        }
    }

}