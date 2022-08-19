package HexEngine;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.util.ArrayList;
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
	private boolean isOneStart;
	private int numberOfSteps;
	private boolean isSave = true;
	Vector<Location> freeCells;
//	private boolean isEnded;
//	private boolean pTest(Location current, std::list<Location>& scannedLocations);		                           	// for testing recursively if current user is completed the path from the given location;
//	private virtual boolean isUserLocationOwner(const Location myLocation);
//	private virtual boolean isLocationCorrect(const Location myLocation) const;												// check if given Location is correct (if its on the matrix or not)
//	private virtual list<Location> findConnections(const Location myLocation) const;		                            	// finds the Locations around a Location (neighbours)

	public boolean getIsOneStart(){return isOneStart;}
	public void setIsOneStart(boolean b){isOneStart = b;}

	public void changePlayerTurn() {
		if (playerTurn == 1)
			playerTurn = 2;
		else if (playerTurn == 2)
			playerTurn = 1;
	}      

	public int getStep(){
		return numberOfSteps;
	}
	public void setSave(boolean save){
		isSave = save;
	}
	
	public Hex(int boardSize, String user1, String user2) throws Exception
	{
		username1 = user1;
		username2 = user2;
		playerTurn = 1;
		numberOfSteps = 0;
		lastLocation = new Location(-1,-1);
		
		matrix = new Vector<Vector<CellState>>();
		setSize(boardSize);
		boolean flag;
		File hexDirectory = new File("/mnt/sdcard/Hex" );
		if(! hexDirectory.exists() )
			hexDirectory.mkdir();
		File directory = new File("/mnt/sdcard/Hex/Current" );
		if(! directory.exists() )
			directory.mkdir();

		else
			deleteOldFiles();


		writeToFile( "/mnt/sdcard/Hex/Current/step0" );

	}

	private void deleteOldFiles() {
		File files = new File("/mnt/sdcard/Hex/Current" );

		for (File file1:files.listFiles()) {
			file1.delete();
		}
	}


	public static Hex readFromFile(String fileName) throws Exception {									// reads game from a file

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



	public boolean writeToFile(String fileName) throws Exception {									// writes game to a file
		
		fileName += ".hex";
		FileOutputStream fileout = null;
		ObjectOutputStream out = null; 
		if( new File(fileName).exists() )
			throw new Exception( "There is saved game with " + fileName + " name. Try another name.");
		
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
	public void reset() {											// resets the board
		
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				setCell(i, j, CellState.DOT );
		numberOfSteps = 0;
	}




	@Override
	public void setSize(int size) throws Exception {							// sets boardsize again
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
			for (int j = 0; j < boardSize; j++)													// finds free cells
				if (getCell(i,j) == CellState.DOT)
					freeCells.add(new Location(i, j));


		Random rand = new Random();
		int randomIndex = rand.nextInt(freeCells.size());

		play(freeCells.elementAt(randomIndex));
	}




	@Override
	public void play(Location location) throws Exception {						// plays the given location
		if(!isLocationCorrect(location))
			throw new Exception("The given location is not correct ");

		if(getCell(location) != CellState.DOT )
			throw new Exception("The given location is not free");


		if (playerTurn == 1)														// if user turn is 1
			setCell(location, CellState.USER1) ;

		else if (playerTurn == 2)
			setCell(location, CellState.USER2); 				// if turn is 2	

		
		lastLocation = location;
		numberOfSteps++;
		changePlayerTurn();
		if(isSave)
			writeToFile( "/mnt/sdcard/Hex/Current/step" + numberOfSteps );
	}




	@Override
	public boolean isEnd() throws Exception {											// controls if the game is end or not
		changePlayerTurn();
		Location loc = new Location(0,0);
		boolean flag = false;

		List<Location> scannedLocations = new ArrayList<>();
		if (getPlayerNow().equals(getUserName2()))										// if player is 2
		{
			for (int j = 0; j < boardSize; j++)						// checks all first border of user 2
			{
				loc.set_x(j);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					flag = true;
			}
			
		}
		if(getPlayerNow().equals(getUserName1()))											// if player is 1
		{
			loc.set_x(0);
			for (int i = 0; i < boardSize; i++)						// checks all location of first border one by one
			{
				loc.set_y(i);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					flag = true;
			}
			if(getPlayerNow() == getUserName1() && flag == false)
			{
			//	changePlayerTurn();
			//	flag = isEnd();
			//	changePlayerTurn();
			}
			
		}
		changePlayerTurn();
		return flag;
	}
	
	
	
	
	
	private boolean pTest(Location current, List<Location> scannedLocations) throws Exception            // for testing if current user is completed the path from the location
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


	public List<Location> getFreeCells(){
		freeCells = new Vector<Location>();
		for (int i = 0; i < getBoardSize(); i++)
			for (int j = 0; j < getBoardSize(); j++)								// finds free cells
				if (getCell(i,j) == Hex.CellState.DOT)
					freeCells.add(new Location(i, j));
		return freeCells;
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


	public List<Location> findConnections(Location myLocation) throws Exception                                                // finds the Locations around a Location (neighbours)
	{
		if(!isLocationCorrect(myLocation))
			throw new Exception("The given location is not correct to find connections.");						// if location is not correct
		List <Location> connections = new ArrayList<>() ;

		
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

		return connections;
	}
	
	
	



	@Override
	public Location lastMove() throws Exception 									// returns the last move (location)
	{ 	
		if (lastLocation.get_x() == -1 && lastLocation.get_y() == -1)
			throw new Exception("There is no last move.");
		return lastLocation;
	
	}

	


	@Override
	public CellState getCell(int i, int j) {									// returns the state of cell
		return matrix.elementAt(i).elementAt(j);
	}




	public void setCell(int i, int j, CellState cs) {								// sets the cell
		matrix.elementAt(i).set(j, cs);
	}




	@Override
	public CellState getCell(Location location) {
		return matrix.elementAt(location.get_x()).elementAt(location.get_y());				//	returns cell by location
	}




	@Override
	public void setCell(Location location, CellState cs) {
		matrix.elementAt(location.get_x()).set(location.get_y(), cs);
	}


	@Override
	public String getPlayerNow() {
		String name = playerTurn == 1 ? username1 : username2;								// returns player now
		return name;
	}


	@Override
	public void print() {																			// prints the board
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
	public int compareTo(Hex other) {														// compare with other board
		if( numberOfSteps > other.numberOfSteps )
			return 1 ;
		if( numberOfSteps < other.numberOfSteps )
			return -1;
		else
			return 0;
	}


	@Override
	public boolean undo() throws Exception {														// returns last state of board
		if(numberOfSteps == 0)
			return false;
		
		try {
		Hex undo = readFromFile("/mnt/sdcard/Hex/Current/step"+(numberOfSteps-1));
		boardSize = undo.boardSize;
		lastLocation = undo.lastLocation;
		matrix = undo.matrix;
		numberOfSteps = undo.numberOfSteps;
		playerTurn = undo.playerTurn;
		
		File Todelete = new File("/mnt/sdcard/Hex/Current/step"+(numberOfSteps+1) + ".hex");
		Todelete.delete();
		return true;
		}
		
		catch (Exception e) {
			return false;
		}
	}


	@Override
	public void setUserName1(String user1) {										// sets username1
		username1 = user1;
		
	}


	@Override
	public void setUserName2(String user2) {										// sets username2
		username2 = user2;
	}


	@Override
	public String getUserName1() {													// gets username1
		return username1;
	}


	@Override
	public String getUserName2() {													// gets username2
		return username2;
	}


	@Override
	public int getBoardSize() {															// returns board size
		return boardSize;
	}


	@Override
	public void save(String name) throws Exception {								// saving game with all steps


			File directory = new File("/mnt/sdcard/Hex/savedGames");
			if(!directory.exists())
				directory.mkdir();
			directory = new File("/mnt/sdcard/Hex/savedGames/"+name);
			if(directory.exists())
				throw new Exception("There is also a saved game with given name.");
				directory.mkdir();

			File file = new File( "/mnt/sdcard/Hex/Current"+ File.separator +"step0.hex");
			File dest = new File ( "/mnt/sdcard/Hex/savedGames" + File.separator+name + File.separator +"step0.hex");
			int i=0;
			while(file.exists())
			{
				copy(file, dest);
				i++;
				file = new File("/mnt/sdcard/Hex/Current"+ File.separator +"step" + i + ".hex");
				dest = new File ("/mnt/sdcard/Hex/savedGames" + File.separator+name + File.separator +"step"+ i + ".hex");
			}

			if(!directory.exists())
				throw new Exception("The app is not allowed to write any file");

	}

	public static List<String> getSavedGamesNames(){												// returns the list of all board
		List<String> names = new ArrayList<>();
		File directory = new File("/mnt/sdcard/Hex/savedGames");
		File[] files = directory.listFiles();
		for (File file : files) {
			if (file.isDirectory()) {
				names.add(file.getName());
			}
		}
		return names;
	}

	private void copy(File src, File dst) throws IOException {											// copies a file from a source to destination
		try (InputStream in = new FileInputStream(src)) {
			try (OutputStream out = new FileOutputStream(dst)) {
				// Transfer bytes from in to out
				byte[] buf = new byte[1024];
				int len;
				while ((len = in.read(buf)) > 0) {
					out.write(buf, 0, len);
				}
			}
		}
	}


	@Override
	public void load(String name) throws Exception {												// loads saved game from storage

		deleteOldFiles();
		if( ! new File("/mnt/sdcard/Hex/savedGames/" + name).exists() )
			throw new Exception("Couldn't find the saved game with given name");
		
		File toLoad = new File("/mnt/sdcard/Hex/savedGames/"+name+ "step0.hex");
		int i=0;
		while( new File("/mnt/sdcard/Hex/savedGames/"+name+ "/step"+i+".hex").exists() )
		{
			toLoad = new File("/mnt/sdcard/Hex/savedGames/"+name+ "/step"+i+".hex");
			i++;
		}
		Hex newHex = null;
		newHex = readFromFile("/mnt/sdcard/Hex/savedGames/"+name+ "/step"+(i-1));

		boardSize = newHex.boardSize;
		lastLocation = newHex.lastLocation;
		matrix = newHex.matrix;
		numberOfSteps = newHex.numberOfSteps;
		playerTurn = newHex.playerTurn;
		username1 = newHex.username1;
		username2 = newHex.username2;
		
		File dest = new File( "/mnt/sdcard/Hex/Current/step0.hex");
		File file = new File ( "/mnt/sdcard/Hex/savedGames" + File.separator+name + File.separator +"step0.hex");
		i=0;
		while(file.exists())
		{
			copy(file,dest);
			i++;
			dest = new File("/mnt/sdcard/Hex/Current"+ File.separator +"step" + i + ".hex");
			file = new File ("/mnt/sdcard/Hex/savedGames" + File.separator+name + File.separator +"step"+ i + ".hex");
			
		}

	}


	
	@Override
	public Object clone() throws CloneNotSupportedException {										// clones the hex object
		// TODO Auto-generated method stub
		
		Hex clone = (Hex)super.clone();
		clone.matrix = new Vector<Vector<CellState>>();
		for(Vector<CellState> row : matrix)
		{
			Vector<CellState> newRow= new Vector<CellState>();
			for(CellState cs : row)
			{
				newRow.add(cs);
			}
			clone.matrix.add(newRow);
		}
		return clone;
	}



	
}
