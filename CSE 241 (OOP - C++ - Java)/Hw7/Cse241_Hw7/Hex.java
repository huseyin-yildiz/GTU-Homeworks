package Cse241_Hw7;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Random;
import java.util.Vector;


public class Hex implements IHex, Serializable, Comparable<Hex>, Cloneable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -8271807803963071982L;


	public enum CellState {
		 NOPE(' ')			// ' '
		,USER1('o') 		// 'o'
		,USER2('x')			// 'x'
		,DOT('.');			// '.'
	
		public char asChar() {
	        return asChar;
	    }

	    private final char asChar;

	    CellState(char asChar) {
	        this.asChar = asChar;
	    }
		
	}
	
	
	private Vector<Vector<CellState>> matrix;
	private short playerTurn;
	private Location lastLocation;
	private int boardSize;
	private String username1, username2;
	
	
	private int numberOfSteps;
//	private boolean isEnded;
//	private boolean pTest(Location current, std::list<Location>& scannedLocations);		                           	// for testing recursively if current user is completed the path from the given location;
//	private virtual boolean isUserLocationOwner(const Location myLocation);
//	private virtual boolean isLocationCorrect(const Location myLocation) const;												// check if given Location is correct (if its on the matrix or not)
//	private virtual list<Location> findConnections(const Location myLocation) const;		                            	// finds the Locations around a Location (neighbours)

	
	public void changePlayerTurn() {
		if (playerTurn == 1)
			playerTurn = 2;
		else if (playerTurn == 2)
			playerTurn = 1;
	}      
	
	
	Hex(int boardSize, String user1, String user2) throws Exception
	{
		username1 = user1;
		username2 = user2;
		playerTurn = 1;
		numberOfSteps = 0;
		lastLocation = new Location(-1,-1);
		
		matrix = new Vector<Vector<CellState>>();
		setSize(boardSize);
		
		File directory = new File("Current" + File.separator);
		if(! directory.exists() )
			directory.mkdir();
		else
		{
			int i=0;
			File file = new File("Current" + File.separator + "step0"+".hex" );
			while(file.exists())
			{
				file.delete();
				i++;
				file = new File("Current" + File.separator + "step"+ i + ".hex" );
			}
		}
	}




	public static Hex readFromFile(String fileName) throws Exception {
		
		fileName += ".hex";
		
		FileInputStream fileIn = null;
		ObjectInputStream in = null; 
		if( ! new File(fileName).exists() )
			throw new Exception( "There is no any saved game with " + fileName + " name. Try another name.");
		
		try {
			fileIn = new FileInputStream(fileName);
			in = new ObjectInputStream(fileIn);
			return (Hex)in.readObject();
		}
		
		catch (IOException e) {
			e.printStackTrace();
			return null;	
		}
		
		finally {
			if(in != null)
				in.close();
			
			if(fileIn != null)
				fileIn.close();
		}
		
	}




	public boolean writeToFile(String fileName) throws Exception {
		
		fileName += ".hex";
		FileOutputStream fileout = null;
		ObjectOutputStream out = null; 
//		if( new File(fileName).exists() )
	//		throw new Exception( "There is saved game with " + fileName + " name. Try another name.");
		
		try {
			fileout = new FileOutputStream(fileName);
			out = new ObjectOutputStream(fileout);
			out.writeObject(this);

			return true;
		}
		
		catch (IOException e) {
			e.printStackTrace();
			return false;
			
		}
		
		finally {
			if(out != null)
				out.close();
			
			if(fileout != null)
				fileout.close();
		}
		
	}




	@Override
	public void reset() {
		
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				setCell(i, j, CellState.DOT );
		numberOfSteps = 0;
	}




	@Override
	public void setSize(int size) throws Exception {
		matrix.clear();

		if (size > 5 && size < 32)
		{
			for (int i = 0; i < size; i++)
			{
				Vector<CellState> row = new Vector<CellState>();
				for (int j = 0; j < size; j++)
					row.add(CellState.DOT);
				matrix.add(row);
			}
			boardSize = size;
		}
		else
			throw new Exception("Size cant be" + size + "size should be larger than 5 and smaller than 32");
	
	}




	@Override
	public void play() throws Exception {
		if (playerTurn == 1)																// checking if player turn is 2 or not 
			throw new Exception("This is from play() function: player turn is not 2. Computer can not play now.");

		Vector<Location> freeCells = new Vector<Location>();
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)								// finds free cells
				if (getCell(i,j) == CellState.DOT)
					freeCells.add(new Location(i, j));


		Random rand = new Random();
		int randomIndex = rand.nextInt(freeCells.size());

		play(freeCells.elementAt(randomIndex));
	}




	@Override
	public void play(Location location) throws Exception {

		if (playerTurn == 1)																// if user turn is 1 
			setCell(location, CellState.USER1) ;

		else if (playerTurn == 2)
			setCell(location, CellState.USER2); 				// if turn is 2	

		
		lastLocation = location;
		numberOfSteps++;
		changePlayerTurn();
		writeToFile( "Current/step" + numberOfSteps );
	}




	@Override
	public boolean isEnd() {
		
		Location loc = new Location(0,0);
		boolean flag = false;
		print();
		
		List<Location> scannedLocations = new ArrayList<>();
		if (!flag)										// if player is 2 
		{
			for (int j = 0; j < boardSize; j++)						// checks all first border of user 2
			{
				loc.set_x(j);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					flag = true;
			}
			
		}
		if(!flag)											// if player is 1
		{
			for (int i = 0; i < boardSize; i++)						// checks all location of first border one by one
			{
				loc.set_y(i);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					flag = true;
			}
			if(getPlayerNow() == getUserName1() && flag == false)
			{
				changePlayerTurn();
				flag = isEnd();
				changePlayerTurn();
			}
			
		}
		return flag;
	}
	
	
	
	
	
	private boolean pTest(Location current, List<Location> scannedLocations)			// for testing if current user is completed the path from the location
	{
		CellState state;
		Location lastBorder = new Location();
		if (playerTurn == 1)
		{
			state = CellState.USER1;
			lastBorder.setLocation(boardSize - 1, -1);								// sets the last border if user 1 and 2
		}

		if (playerTurn == 2)
		{
			state = CellState.USER2;
			lastBorder.setLocation(-1, boardSize -1 );
			
		}

		boolean inScanned = false;
		for(Location loc : scannedLocations)
			if(current.get_x() == loc.get_x() && current.get_y() == loc.get_y() )
				inScanned = true;
		
		if (!isUserLocationOwner(current) || inScanned)
		{
			if (!inScanned)												// if it is not scanned then we add it to scanneds
				{
					Location adding = new Location(current.get_x(), current.get_y());
					scannedLocations.add(adding);
				}
				return false;
		}
		else
		{
			if ((lastBorder.get_x() == current.get_x() || lastBorder.get_y() == current.get_y()))	// if the location is on the last border
				return true;																		// then return true (path is completed)
			else
				scannedLocations.add(current);

			List<Location> neighbours = findConnections(current);
			for (Location x : neighbours)															// looks to the neighbours
			{
				//			bool found = find(neighbours.begin(), neighbours.end(), x) != neighbours.end();
				if (isLocationCorrect(x) && isUserLocationOwner(x))
					if (pTest(x, scannedLocations))
						return true;
			}

		}
		return false;
	}

	
	
	
	
	private boolean isUserLocationOwner(Location myLocation)
	{																								// check if the user is Location owner
		short owner = 0;
		char locationValue = getCell(myLocation.get_x(), myLocation.get_y()).asChar() ;
		if (locationValue == CellState.USER1.asChar() )
			owner = 1;
		else if ( locationValue == CellState.USER2.asChar() )
			owner = 2;

		return owner == playerTurn ? true : false;

	}

	private boolean isLocationCorrect( Location myLocation )											// check if given Location is correct (if its on the matrix or not)
	{
		if (myLocation.get_x() >= boardSize || myLocation.get_y() >= boardSize || myLocation.get_x() < 0 || myLocation.get_y() < 0)
			return false;
		return true;
	}


	List<Location> findConnections(Location myLocation) 												// finds the Locations around a Location (neighbours)
	{
		List <Location> connections = new ArrayList<>() ;

	//	if(isLocationCorrect(myLocation))
	//		connections.add(myLocation);
		
		if(isLocationCorrect(myLocation.changeLocation(-1, 0)))	
			connections.add(myLocation.changeLocation(-1, 0));
		
		if(isLocationCorrect(myLocation.changeLocation(1, 0)))	
			connections.add(myLocation.changeLocation(1, 0));
		
		if(isLocationCorrect(myLocation.changeLocation(0, -1)))	
			connections.add(myLocation.changeLocation(0, -1));
		
		if(isLocationCorrect(myLocation.changeLocation(0, 1)))	
			connections.add(myLocation.changeLocation(0, 1));
		
		if(isLocationCorrect(myLocation.changeLocation(-1, 1)))	
			connections.add(myLocation.changeLocation(-1, 1));
		
		if(isLocationCorrect(myLocation.changeLocation(1, -1)))	
			connections.add(myLocation.changeLocation(1, -1));


	//	java.util.Iterator<Location> it = connections.iterator();
	//	while (it.hasNext() )
	//		if( !isLocationCorrect(it.next()) )
	//			it.remove();

		return connections;
	}
	
	
	



	@Override
	public Location lastMove() throws Exception 
	{ 	
		if (lastLocation.get_x() == -1 && lastLocation.get_y() == -1)
			throw new Exception("There is no last move.");
		return lastLocation;
	
	}

	


	@Override
	public CellState getCell(int i, int j) {
		return matrix.elementAt(i).elementAt(j);
	}




	public void setCell(int i, int j, CellState cs) {
		matrix.elementAt(i).set(j, cs);
	}




	@Override
	public CellState getCell(Location location) {
		return matrix.elementAt(location.get_x()).elementAt(location.get_y());
	}




	@Override
	public void setCell(Location location, CellState cs) {
		matrix.elementAt(location.get_x()).set(location.get_y(), cs);
	}


	@Override
	public String getPlayerNow() {
		String name = playerTurn == 1 ? username1 : username2;
		return name;
	}


	@Override
	public void print() {
		System.out.print("  ");
		for (int letter = 0; letter < boardSize; letter++)
			System.out.print( Character.toString( (char)('a' + letter)) + " "  );
		System.out.println();
		for (int i = 0; i < boardSize; i++)
		{
			System.out.print( i + 1);
			System.out.print(" ");
			for (int space = 0; space < (i > 8 ? i - 1 : i); space++)
				System.out.print(" ");

			for (int j = 0; j < boardSize; j++)
			{
				System.out.print( getCell(i, j).asChar()  + " "  );
			}
			System.out.println();
		}
		
	}


	@Override
	public int compareTo(Hex other) {
		if( numberOfSteps > other.numberOfSteps )
			return 1 ;
		if( numberOfSteps < other.numberOfSteps )
			return -1;
		else
			return 0;
	}


	@Override
	public boolean undo() throws Exception {
		if(numberOfSteps == 0)
			return false;
		
		try {
		Hex undo = readFromFile("Current/step"+(numberOfSteps-1));
		boardSize = undo.boardSize;
		lastLocation = undo.lastLocation;
		matrix = undo.matrix;
		numberOfSteps = undo.numberOfSteps;
		playerTurn = undo.playerTurn;
		
		File Todelete = new File("Current/step"+(numberOfSteps+1) + ".hex");
		Todelete.delete();
		return true;
		}
		
		catch (Exception e) {
			return false;
		}
		
	}


	@Override
	public void setUserName1(String user1) {
		username1 = user1;
		
	}


	@Override
	public void setUserName2(String user2) {
		username2 = user2;
	}


	@Override
	public String getUserName1() {
		return username1;
	}


	@Override
	public String getUserName2() {
		return username2;
	}


	@Override
	public int getBoardSize() {
		return boardSize;
	}


	@Override
	public boolean save(String name) throws IOException {								// saving game with all steps
		try {
			File directory = new File("savedGames"+ File.separator + name);
			if(!directory.exists())
				directory.mkdir();
			File file = new File( "Current"+ File.separator +"step0.hex");
			File dest = new File ( "savedGames" + File.separator+name + File.separator +"step0.hex");
			int i=0;
			while(file.exists())
			{
				Files.copy( file.toPath() , dest.toPath()  , StandardCopyOption.REPLACE_EXISTING );
				i++;
				file = new File("Current"+ File.separator +"step" + i + ".hex");
				dest = new File ("savedGames" + File.separator+name + File.separator +"step"+ i + ".hex");
				
			}
			return true;
		}
		
		catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	}


	@Override
	public boolean load(String name) throws Exception {
		if( ! new File("savedGames/" + name).exists() )
			return false;
		
		File toLoad = new File("savedGames/"+name+ "step0.hex");
		int i=0;
		while( new File("savedGames/"+name+ "/step"+i+".hex").exists() )
		{
			toLoad = new File("savedGames/"+name+ "/step"+i+".hex");
			i++;
		}
		Hex newHex = readFromFile("savedGames/"+name+ "/step"+(i-1));
		boardSize = newHex.boardSize;
		lastLocation = newHex.lastLocation;
		matrix = newHex.matrix;
		numberOfSteps = newHex.numberOfSteps;
		playerTurn = newHex.playerTurn;
		username1 = newHex.username1;
		username2 = newHex.username2;
		
		File dest = new File( "Current/step0.hex");
		File file = new File ( "savedGames" + File.separator+name + File.separator +"step0.hex");
		i=0;
		while(file.exists())
		{
			Files.copy( file.toPath() , dest.toPath()  , StandardCopyOption.REPLACE_EXISTING );
			i++;
			dest = new File("Current"+ File.separator +"step" + i + ".hex");
			file = new File ("savedGames" + File.separator+name + File.separator +"step"+ i + ".hex");
			
		}
		
		return true;
	}


	
	@Override
	protected Object clone() throws CloneNotSupportedException {
		// TODO Auto-generated method stub
		
		Hex clone = (Hex)super.clone();
		clone.matrix = new Vector<Vector<CellState>>();
		for(Vector<CellState> row : matrix)
		{
			Vector<CellState> newRow= new Vector<Hex.CellState>(); 
			for(CellState cs : row)
			{
				newRow.add(cs);
			}
			clone.matrix.add(newRow);
		}
		return clone;
	}







	



	
	
}
