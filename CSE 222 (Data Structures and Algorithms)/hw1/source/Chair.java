/** The class for Chairs */
public class Chair extends Product {

	/** Initializes the Chair with given arguments */
	public Chair( String modelName, Color color,float price) throws Exception {
		super(modelName, color,price);	
	}
	
	/** Initializes the Chair with given arguments without color (Used for multiple colors) */
	public Chair( String modelName, float price) throws Exception {
			super(modelName,price);
		}

}
