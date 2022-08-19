
public class MeetingTable extends Product {
	
	/** Initializes the Meeting Table with given arguments */
	public MeetingTable( String modelName, Color color,float price) throws Exception {
		super(modelName, color,price);
	
	}
	
	/** Initializes the Meeting Table with given arguments without color (Used for multiple colors) */
	public MeetingTable( String modelName, float price) throws Exception {
		super(modelName,price);
	}

}
