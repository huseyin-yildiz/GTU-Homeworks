/**
 * The User service interface for the all operations about users
 */
public interface IUserService {
    /**
     * login the user with user id and password
     * @param userId
     * @param password
     * @return user object
     * @throws Exception if the id and password not correct
     */
    public User login(Integer userId, String password) throws Exception;

    /**
     * adds the given user to the system
     * @param user the user to be added
     */
    public void addUser(User user);

    /**
     * Removes the user from system
     * @param userId the user to be removed
     */
    public void removeUser(int userId);

    /**
     * finds and returns the user by id
     * @param userId user id to be search
     * @return user object
     */
    public User getUserById(Integer userId);
}
