/*
 *	The class for Bookcase 
 */
public class BookCase extends Product {

	/** Constructor for initialize with color */
	public BookCase( String modelName, Color color,float price) throws Exception {
		super(modelName, color,price);
	}
	
	/** Constructor for initialize without color (Used for adding multi color) */
	public BookCase( String modelName, float price) throws Exception {
		super(modelName,price);
	}

}
