package HexEngine;


public interface IHex {

	public void reset();
	public void setSize(int size) throws Exception	;
	public void play() throws Exception;
	public void play(Location location) throws Exception;
	public boolean isEnd() throws Exception;
 	public Hex.CellState getCell(int i, int j);
 	public Hex.CellState getCell(Location location);
 	public void setCell(Location location, Hex.CellState cs);
 	public Location lastMove() throws Exception;
	public String getPlayerNow(); 
	public boolean undo() throws Exception;
	public void setUserName1(String user1);
	public void setUserName2(String user2);
	public String getUserName1();
	public String getUserName2();
	public int getBoardSize();
	public void save(String name) throws Exception;


	public void load(String name) throws Exception;
	public void print();
	
}
