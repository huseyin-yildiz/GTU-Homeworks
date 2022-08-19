
import java.util.Iterator;

import Containers.IContainer;


/**
 * 
 */

/**
 * @author Mehmet Huseyin YILDIZ
 * The class for administrator 
 */
public class Administrator extends Employee {

	private IRepository repository;
	
	
	/**
	 * @param name
	 * @param surname
	 * @param mail
	 * @param password
	 */
	public Administrator(String name, String surname, String mail, String password) {
		super(name, surname, mail, password);
		repository = getRepository();
	}

	
	/** adds a user (Employee, customer or Administrator ) to system  */
	public void addUser(User user) throws Exception {										// amortised θ(1)
		repository.addUser(user);								
	}
	
	/** removes a user (Employee, customer or Administrator ) in system */
	public void removeUser(User user) throws Exception {							// O(1)
		repository.removeUser(user);
	}
	
	/** adds a branch */
	public void addBranch(String branchName) throws Exception {						// amortised θ(1)
		Branch branch = new Branch(branchName);
		repository.addBranch(branch);
	}
	/** removes branch with branch name*/
	public void removeBranch(String branchName) throws Exception {						//  O(n)
		Iterator<Branch> it = repository.getBranches().iterator();
		while(it.hasNext())
		{
			Branch branch = it.next();
			if(branch.getName().equals(branchName))
				{
					repository.removeBranch(branch);
					return;
				}
		}
		throw new Exception("The given branch name doesnt exist to remove");
	}
	
	/** returns product requirement messages sent by branch employees */
	public IContainer<Message> getProductInforms(){										//  θ(1)
		return repository.getMessages();
	}
	
	
	

}
