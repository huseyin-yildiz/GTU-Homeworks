
public class OfficeDesk extends Product {

	/** Initializes the Office Desk with given arguments  */
	public OfficeDesk( String modelName, Color color, float price) throws Exception {
		super( modelName, color, price);

	}
	/** Initializes the Office Desk with given arguments without color (Used for multiple colors) */
	public OfficeDesk( String modelName, float price) throws Exception {
		super(modelName,price);
	}
}
