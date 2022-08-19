package Cse241_Hw7;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;

enum CellState {
	Free,
	User1,
	User2
}

public class CellButton extends JButton {

	private static final long serialVersionUID = 1L;

	private Location location;
	
	CellButton( CellState cellState){
		super();
		super.setPreferredSize(new Dimension(40, 40));
		
		switch (cellState) {
		
			case Free  : makeWhite(); break; 
			case User1 : makeBlue(); break; 
			case User2 : makeRed();	 break; 
			default:
				throw new IllegalArgumentException("Unexpected value: " + cellState);
		
		}
	
	}
	
	

	public void setLoc(Location loc) {
		location = loc ;
	}
	
	
	public Location getLoc() {
		return location;
	}
	
	public void makeBlue() {
		setBackground(Color.blue);	}
	
	public void makeRed() {
		setBackground(Color.red);
	}
	
	public void makeWhite() {
		setBackground(Color.white);
	}



}
