import java.io.Serializable;

/**
 * The abstract User class for Trader and User
 */
public abstract class User implements Identifiable, Serializable {
    private final int id;
    private String name;
    private String surname;
    private String password;
    private String phoneNumber;

    /**
     * The constructor of the User class
     * @param name  the name of the User
     * @param surname  the surname of the User
     * @param password the password of the User
     * @param phoneNumber the phone number of the User
     */
    public User(String name, String surname, String password, String phoneNumber){
        id = UserService.getInstance().getNewId();
        this.name = name;
        this.surname = surname;
        this.password = password;
        this.phoneNumber = phoneNumber;
    }

    /**
     * returns the id of the user
     */
    public Integer getId() {
        return id;
    }

    /**
     * returns the name of the user
     */
    public String getName() {
        return name;
    }

    /**
     * sets the name of the user
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * returns the surname of the user
     */
    public String getSurname() {
        return surname;
    }

    /**
     * sets the surname of the user
     */
    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    @Override
    public int compareTo(Object o) {
        User other = ((User) o);
        return getId().compareTo(other.getId());
    }

    @Override
    public String toString() {
        return "Name: "+name +" Surname:"+surname+" Password:"+password+" PhoneNumber:"+phoneNumber;
    }
}
