package Cse241_Hw7;

import java.io.Serializable;

public class Location implements Serializable,Cloneable {
	

	/**
	 * 
	 */
	private static final long serialVersionUID = 7556794030623375123L;
	private int x;
	private int y;
	
	
	public Location() {	    setLocation(-1, -1);	}
	
	public Location(int x, int y) {     setLocation(x, y); }
	
	public void setLocation(int x_, int y_) { x = x_; y = y_; }
	
	public void set_x(int x_) { x = x_; }
	
	public void set_y(int y_) { y = y_; }
	
	public int get_y() { return y; }
	
	public int get_x() { return x; }
	
	public void setByAdding(int x_, int y_)  
	{
		x += x_;
		y += y_; 
	}
	
	public Location changeLocation(int x_, int y_)  
	{
	    Location newLocation = new Location();
	    newLocation.set_x(x + x_);
	    newLocation.set_y(y + y_);
	    return newLocation;
	}
	
	// public friend std::istream& operator>> (std::istream& in, Location location);

	// bool operator==(Location another)const;
	
	
	
	@Override
	protected Object clone() throws CloneNotSupportedException {
		return super.clone();
	}


}


