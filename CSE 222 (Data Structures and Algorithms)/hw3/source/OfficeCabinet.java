
public class OfficeCabinet extends Product {

	
	/** Initializes the Office Cabinet with given arguments */	
	public OfficeCabinet( String modelName, Color color,float price) throws Exception {
		super(modelName, color,price);
		
	}
	
	/** Initializes the Office Cabinet with given arguments without color (Used for multiple colors) */
	public OfficeCabinet( String modelName, float price) throws Exception {
		super(modelName,price);
	}

}
