import java.io.*;
import java.util.HashMap;
import java.util.Hashtable;

/**
 * The User service class for the all operations about users
 */
public class UserService implements IUserService ,Serializable{

    private static UserService userService;

    private HashMap<Integer,User> users;
    private final static String fileName = "users.txt";
    private Integer lastId;

    private UserService(){
            if( ! loadUsers() )
                users = new HashMap<>();
    }

    public static UserService getInstance(){
        if(userService == null)
            userService = new UserService();
        return userService;
    }

    @Override
    public User login(Integer userId, String password) throws Exception {
        User user = users.get(userId);
        if(user != null && user.getPassword().equals(password))
            return user;
        else
            throw new Exception("The username or password is wrong");
    }

    @Override
    public void addUser(User user) {
        users.put(user.getId(),user);
        //saveUsers();
    }

    public int getNewId(){
        if(userService.lastId == null)
            userService.lastId = 10000000;
        else
            userService.lastId++;

        return userService.lastId;
    }

    @Override
    public void removeUser(int userId) {
        users.remove(userId);
        saveUsers();
    }

    @Override
    public User getUserById(Integer userId) {
        return users.get(userId);
    }

    public void saveUsers(){
        try {
            FileOutputStream fileOut = new FileOutputStream(fileName);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(userService);
            objectOut.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean loadUsers(){
        try {
            FileInputStream fileIn = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            userService = (UserService) in.readObject();
            if(userService != null) {
                users = userService.users;
                lastId = userService.lastId;
            }
            in.close();
            fileIn.close();
            if(users != null)
                return true;
        } catch (IOException e) {
            //e.printStackTrace();
            return false;
        } catch (ClassNotFoundException c) {
            System.out.println("HashMap class not found");
            c.printStackTrace();
            return false;
        }
        return false;
    }

    public static void main(String args[]){                     // Tests
        UserService userService = UserService.getInstance();

   //     Trader trader = new Trader("Ali","YILMAZ","123456","05511453478");
     //   userService.addUser(trader);

        User user = userService.getUserById(10000001);
        if(user != null)
            System.out.println(user.getName()+" "+user.getSurname() + " "+userService.lastId);

        try {
            user = null;
            user = userService.login(10000000,"123456");
            System.out.println(user.getName()+" "+user.getSurname() + " "+user.getId());
            userService.removeUser(10000000);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
