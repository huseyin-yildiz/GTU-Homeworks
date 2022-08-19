/** The class for messages between users. Like informing administrator about product */
public class Message implements Identifiable {

	private String id;
	private static int idCounter = 0;
	private String text;
	private User sender;
	
	/** Initializes by taking text and sender */
	public Message(String text, User sender) {						//  θ(1)
		++idCounter;
		id = Integer.toString(idCounter);
		setText(text);
		this.sender = sender;
	}

	/**
	 * @return the text
	 * returns message text
	 */
	public String getText() {									//  θ(1)
		return text;
	}

	/**
	 * @param text the text to set
	 * sets message text
	 */
	public void setText(String text) {						//  θ(1)
		this.text = text;
	}

	/**
	 * @return the sender
	 * returns sender text 
	 */
	public User getSender() {								//  θ(1)
		return sender;
	}

	/** returns the id of message */
	@Override
	public String getId() {									//  θ(1)
		return id;
	}

	/** Returns the full name of sender and text as string*/
	@Override
	public String toString() {						//  O(n^2)
		return "From "+ sender.getFullName()+" :" +  getText();
	}
	
}
