package Cse241_Hw7;

import java.awt.Frame;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class main {

	public static void main(String[] args) throws Exception {
		
	/*	MainFrame den = new MainFrame();
		den.setVisible(true);
		den.setSize(500,350);
		HexBoard hexBoard = new HexBoard(8);
		den.add(hexBoard);*/
	
		

		
		Hex myHex = new Hex(8, "user1", "user2");
		SettingsFrame sf = new SettingsFrame(myHex);
		sf.show();
		
		
		
	/*	
		
		
		for(int i=0; i<7; i++)
		{
			myHex.play(new Location(2, i) );
			System.out.println( myHex.isEnd() );

			myHex.play(new Location(5, i) );	
			System.out.println( myHex.isEnd() );
		
		}
		myHex.play(new Location(0, 5) );	
		myHex.play(new Location(5, 7) );	
	
		
		myHex.print();

		myHex.undo();
		myHex.print();
		myHex.changePlayerTurn();
		System.out.println( myHex.isEnd() );*/
	
	
	}

}
