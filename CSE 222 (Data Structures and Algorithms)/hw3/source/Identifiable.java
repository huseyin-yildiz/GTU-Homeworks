
/** The Interface to compare objects by id */
public interface Identifiable {
	/** returns id */
	public String getId();

	/** returns if the taken argument is equals or not */
	@Override
	boolean equals(Object obj);
}
