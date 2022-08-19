package Cse241_Hw7;

import java.io.FileNotFoundException;
import java.io.IOException;

import Cse241_Hw7.Hex.CellState;

public interface IHex {

	public void reset();
	public void setSize(int size) throws Exception	;
	public void play() throws Exception;
	public void play(Location location) throws Exception;
	public boolean isEnd();
 	public Cse241_Hw7.Hex.CellState getCell(int i, int j);
 	public Cse241_Hw7.Hex.CellState getCell(Location location);
 	public void setCell(Location location, CellState cs);
 	public Location lastMove() throws Exception;
	public String getPlayerNow(); 
	public boolean undo() throws Exception;
	public void setUserName1(String user1);
	public void setUserName2(String user2);
	public String getUserName1();
	public String getUserName2();
	public int getBoardSize();
	public boolean save(String name) throws Exception;
	public boolean load(String name) throws Exception;
	public void print();
	
}
