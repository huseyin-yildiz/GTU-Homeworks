/** The class for messages between users. Like informing administrator about product */
public class Message implements Identifiable {

	private String id;
	private static int idCounter = 0;
	private String text;
	private User sender;
	
	/** Initializes by taking text and sender */
	public Message(String text, User sender) {
		++idCounter;
		id = Integer.toString(idCounter);
		setText(text);
		this.sender = sender;
	}

	/**
	 * @return the text
	 * returns message text
	 */
	public String getText() {
		return text;
	}

	/**
	 * @param text the text to set
	 * sets message text
	 */
	public void setText(String text) {
		this.text = text;
	}

	/**
	 * @return the sender
	 * returns sender text 
	 */
	public User getSender() {
		return sender;
	}

	/** returns the id of message */
	@Override
	public String getId() {
		return id;
	}

	/** Returns the full name of sender and text as string*/
	@Override
	public String toString() {
		return "From "+ sender.getFullName()+" :" +  getText();
	}
	
}
