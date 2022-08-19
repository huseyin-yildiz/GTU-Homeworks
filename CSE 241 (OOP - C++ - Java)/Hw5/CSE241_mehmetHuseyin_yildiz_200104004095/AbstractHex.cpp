#include "AbstractHex.h"

namespace Hex
{
	AbstractHex::AbstractHex(string user1, string user2)
	{
		this->username1 = user1;
		this->username2 = user2;
		playerTurn = 1;
		numberOfSteps = 0;
		lastLocation.setLocation(-1,-1);
	}

	bool AbstractHex::isEnd()
	{
		Location loc;
		loc.set_x(0);
		loc.set_y(0);
		list<Location> scannedLocations;
		if (playerTurn == 2)										// if player is 2 
		{
			for (int j = 0; j < boardSize - 1; j++)						// checks all first border of user 2
			{
				loc.set_y(j);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					return true;
			}
			return false;
		}
		else 											// if player is 1
		{
			for (int i = 0; i < boardSize - 1; i++)						// checks all location of first border one by one
			{
				loc.set_x(i);
				if (pTest(loc, scannedLocations))										// if path is found to the last border
					return true;
			}
			return false;
		}
	}

	Location AbstractHex::lastMove() 
	{
		cout << "err";
		if (lastLocation.get_x() == -1 && lastLocation.get_y() == -1)
			throw my_exception("There is no last move.");
		return lastLocation;
	}

	int AbstractHex::numberOfMoves()
	{
		return numberOfSteps;
	}

	string AbstractHex::getPlayerNow()
	{
		string name = playerTurn == 1 ? username1 : username2;
		return name;
	}

	void AbstractHex::clearScreen()
	{
		cout << "\033[2J\033[1;1H";
	}


	void AbstractHex::print()
	{
		cout << "  ";
		for (int letter = 0; letter < boardSize; letter++)
			cout << char('a' + letter) << ' ';
		cout << endl;
		for (int i = 0; i < boardSize; i++)
		{
			cout << i + 1 << ' ';
			for (int space = 0; space < (i > 8 ? i - 1 : i); space++)
				cout << " ";

			for (int j = 0; j < boardSize; j++)
			{
				cout << char(operator()(i, j)) << " ";
			}
			cout << "\n";
		}
	}


	bool AbstractHex::readFromFile(string fileName)
	{
		ifstream inputStream(fileName);
		if (inputStream.fail())
		{
			//cout << game;
			cerr << endl << "The file is not found\n";				// if the given file name is not found gives an error to the user.
			return false;
		}
		else
		{
			inputStream >> boardSize >> numberOfSteps								// if file name is found then start to copy the values row by row.
				>> username1 >> username2;							// each row is for one variable or array
			inputStream.get();
			for (int i = 0; i < boardSize; i++)									// saves the matrix
			{
				for (int j = 0; j < boardSize; j++)
					operator()(i, j) = CellState(inputStream.get());
			}
			inputStream.get();

			int x, y;
			inputStream >> isEnded
				>> playerTurn
				>> x >> y;
			lastLocation.setLocation(x, y);


			inputStream.close();

			cout << "\nThe file loaded successfully\n";							// if the loading is successcfull then gives an output to the user.
			return true;

		}
	}

	bool AbstractHex::writeToFile(string fileName)
	{
		ifstream inputStream(fileName.c_str());
		if (!inputStream.fail() && fileName.substr(1, 4) != "step")														// checks if there is a file with given string
		{
			cerr << "\nThere is a file with this name please try another name... \n";	// if it find a file with given string then it gives an error to try again.
			inputStream.close();
			return false;
		}
		else															// if there is no problem about file name then starts to save information row by row.
		{
			inputStream.close();
			ofstream outputStream(fileName.c_str());

			outputStream << boardSize << ' ' << numberOfSteps << endl
				<< username1 << ' ' << username2 << endl;

			for (int i = 0; i < boardSize; i++)												// saves the matrix array 
			{
				for (int j = 0; j < boardSize; j++)
					outputStream << char(operator()(i, j));
			}

			outputStream << endl << isEnded << endl
				<< playerTurn << endl
				<< lastLocation.get_x() << ' ' << lastLocation.get_y() << endl;

			outputStream << int(';') << endl;

			outputStream.close();
			cout << "The game saved successfully\n";
			return true;
		}
	}


	bool AbstractHex::pTest(Location current, std::list<Location>& scannedLocations)			// for testing if current user is completed the path from the location
	{
		CellState state;
		Location lastBorder;
		if (playerTurn == 1)
		{
			state = CellState::user1;
			lastBorder.setLocation(-1, boardSize - 1);								// sets the last border if user 1 and 2
		}

		if (playerTurn == 2)
		{
			state = CellState::user2;
			lastBorder.setLocation(boardSize - 1, -1);
		}

		bool inScanned = find(scannedLocations.begin(), scannedLocations.end(), current) != scannedLocations.end();
		if (!isUserLocationOwner(current) || inScanned)
		{
			if (!inScanned)												// if it is not scanned then we add it to scanneds
				scannedLocations.push_back(current);
			return false;
		}
		else
		{
			if ((lastBorder.get_x() == current.get_x() || lastBorder.get_y() == current.get_y()))	// if the location is on the last border
				return true;																		// then return true (path is completed)
			else
				scannedLocations.push_back(current);

			auto neighbours = findConnections(current);
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


	bool AbstractHex::isUserLocationOwner(Location myLocation)
	{																								// check if the user is Location owner
		short owner = 0;
		char locationValue = char(operator()(myLocation.get_x(), myLocation.get_y()));
		if (locationValue == (char)CellState::user1)
			owner = 1;
		else if (locationValue == (char)CellState::user2)
			owner = 2;

		return owner == playerTurn ? true : false;

	}

	bool AbstractHex::isLocationCorrect(const Location myLocation) const											// check if given Location is correct (if its on the matrix or not)
	{
		if (myLocation.get_x() >= boardSize || myLocation.get_y() >= boardSize || myLocation.get_x() < 0 || myLocation.get_y() < 0)
			return false;
		return true;
	}


	list<Location> AbstractHex::findConnections(Location myLocation) const			// finds the Locations around a Location (neighbours)
	{
		list <Location> connections;
		connections.push_back(myLocation);
		connections.push_back(myLocation.changeLocation(-1, 0));
		connections.push_back(myLocation.changeLocation(1, 0));
		connections.push_back(myLocation.changeLocation(0, -1));
		connections.push_back(myLocation.changeLocation(0, 1));
		connections.push_back(myLocation.changeLocation(-1, 1));
		connections.push_back(myLocation.changeLocation(1, -1));

		for (auto it = connections.begin(); it != connections.end(); it++)
			if (!isLocationCorrect(*it))
				connections.erase(it--);

		return connections;
	}

	void AbstractHex::changePlayerTurn()
	{
		if (playerTurn == 1)
			playerTurn = 2;
		else if (playerTurn == 2)
			playerTurn = 1;

	}
}