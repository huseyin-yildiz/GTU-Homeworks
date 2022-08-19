
import Containers.IContainer;
import Containers.Iterator;

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
	public void addUser(User user) throws Exception {
		repository.addUser(user);
	}
	
	/** removes a user (Employee, customer or Administrator ) in system */
	public void removeUser(User user) throws Exception {
		repository.removeUser(user);
	}
	
	/** adds a branch */
	public void addBranch(String branchName) throws Exception {
		Branch branch = new Branch(branchName);
		repository.addBranch(branch);
	}
	/** removes branch with branch name*/
	public void removeBranch(String branchName) throws Exception {
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
	public IContainer<Message> getProductInforms(){
		return repository.getMessages();
	}
	
	
	

}
