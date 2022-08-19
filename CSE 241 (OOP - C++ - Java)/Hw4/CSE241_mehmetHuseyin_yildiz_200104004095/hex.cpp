#include<iostream>
#include <algorithm>
#include"hex.h"
#include<list>
#include<string>
#include<random> 
#include<fstream>

using namespace std;

 	int Hex::getBoardSize() 	
	{
		return boardSize;
	}
	bool Hex::isMarkedCellsMore(Hex & anotherHex)										// returns if this board has more marked cells than another
	{
		return numberOfMarkedCells() > anotherHex.numberOfMarkedCells();
	}
	int Hex::MarkedCellsOfAllBoards(vector<Hex> & hexGames)								// returns numbers of all boards (static function)
	{
		int sum = 0;
		for (Hex hexGame : hexGames)
			sum += hexGame.numberOfMarkedCells();
		return sum;
	}

	bool Hex::isLocationEmpty(Location myLocation)													// returns if a location on matrix is empty or not
	{
		if (!isLocationCorrect(myLocation))
			return false;
				if( matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::dot)
					return true;
				return false;				
	}	
	
	Hex::CellMatrix::row& Hex::CellMatrix::operator[](int i) const									// index operator overloading to access matrix class directly
	{
		if(i > size || i<0)
			{
					cout << "wrong location looking on matrix.";
			}
		return matrix[i];
	}
	

	ostream& operator <<(ostream & op, Hex& game)										// for displaying and saving game the last situation of the board				
	{
		if (&op == &cout)														// if it is a display then it displays the board
		{
			op << "  ";
			for (int letter = 0; letter < game.boardSize; letter++)					// the algorithms her is for displaying
				cout << char('a' + letter) << ' ';
			op << endl;
			for (int i = 0; i < game.boardSize; i++)
			{
				op << i + 1 << ' ';
				for (int space = 0; space < (i > 8 ? i - 1 : i); space++)
					op << " ";

				for (int j = 0; j < game.boardSize; j++)
				{
					op << char(game.matrix[i][j].getCellState()) << " ";
				}
				op << "\n";
			}
			
		}
		else																								// if it is a saving
			game.saveGame(game.fName);
		return op;
	}

	

	


	

	Hex::Hex():matrix()
	{
		//intentionally empty
	}

	bool Hex::PlayGame()
	{
	//	while (!isFinished) {													// the game keeps going while the game is not finished.
		cout << *this;																								// ays the board after every playing.
			try {
				//	int locationSize = hexGame.boardSize * hexGame.boardSize /2;
				Location myLocation;

				if (getPlayerTurn() == 1 || user2 != DEFAULT_NAME) 					// if the playerTurn is person
				{
					myLocation = takeLocation();
					if (newGame)
						return false;
					if (isLocationCorrect(myLocation) && isLocationEmpty(myLocation))			// checks the taken location from user
						play(myLocation);			// plays the taken location 			
					else
						cerr << "You entered wrong location please enter again\n";
				}
				else																			// if the player is computer
				{
					play();																		// plays for computer
				}
				if (isFinished)
					showResults();												
				return true;												
			}
			catch (int e) {
				if (e == 20)
					cerr << "You entered wrong location please enter it again";
				else
					cerr << "There is unknown error";
				return false;
			}

			cout << *this;
		}


	        void Hex::menu()																			// shows the main menu and takes preferences
			{
				char selection1;
				int selection;
				bool anyError=false;

				do{
					if(anyError == true){
						cerr<<"\nYou entered wrong number\n";
						anyError = false;
					}
					
				cout<<"1) one-computer \n2) one-one \n";
				cin>>selection1;															// asks for one-one or one-computer
				if(selection1 !='1'  &&  selection1 != '2' )
					anyError = true;
				clearScreen();
				}
				while(anyError);


				cout<<"Name for User 1\n";													// asks for names
				cin>>user1;
				clearScreen();
				if(selection1 == '2')
				{
					cout<<"Name for User 2\n";
					cin>>user2;
					clearScreen();
				}
				
				boardSize:
				cin.clear();
				cin.ignore(100,'\n');
				cout<<"Enter board size Please (Like:7x7): ";										// takes board size
				string a;
				getline(cin,a);
				
				if (a.size() == 3)
				{
					if ((a[0] - '0') < 0 || a[1] != 'x' || a[2] - '0' > 26 || a[0] != a[2])
					{
						cout << "!!! Wrong format please try again: ";									// these algorithms for checking the input
						goto boardSize;
					}
					selection = a[0] - '0';
				}
				else if(a.size() == 5)
				{
					if ( stoi(a.substr(0,2)) < 0 || a[2] != 'x' || stoi(a.substr(3, 2)) > 26 || stoi(a.substr(0, 2)) != stoi(a.substr(3, 2)))
					{
						cout << "!!! Wrong format please try again: ";
						goto boardSize;
					}
					selection = stoi(a.substr(0, 2));
				}
				
				else
				{
					cout << "!!! Wrong format please try again: ";
					goto boardSize;
				}
				
				
				if (selection <= 5)																			// if the input is too short
				{
					cout << selection << " is too short. Press Enter to enter again: ";
					goto boardSize;
				}
				else
					boardSize = selection;
				
                createMatrix();
				
				ofstream iFile("a");
				fName = to_string(gameNow) + "step0";
				iFile << *(this);
			}

			void Hex::play()																	// play function for computer
			{
				Location myLocation;

				if (firstLocationOfUser2.get_x() == -1)											// if it is first playing
					myLocation = firstMovement();
				else
					myLocation = move();


				if (!isLocationCorrect(myLocation) || !isLocationEmpty(myLocation))
					play();
				
				else
					play(myLocation);

			}

			int Hex::getWidth()															// getter of width
			{
				return boardSize*3 -1;
			}

			int Hex::getHeight()														// getter of height
			{
				return boardSize;
			}
	

			
	void Hex::clearScreen()
	{														// clears the screen
				cout << "\033[2J\033[1;1H";
	}

	void Hex::createMatrix()
	{
		this->matrix = CellMatrix(boardSize);
	}

	int Hex::numberOfMarkedCells()							// it return number of marked cells of the object. There is also static function that returns number of markeds for all boards.
	{
		int sum = 0;
		for(int i = 0; i<boardSize; i++)
			for (int j=0; j< boardSize; j++)
			{
				if (matrix[i][j].getCellState() == CellState::user1 || matrix[i][j].getCellState() == CellState::user2)
					sum++;
			}
		return sum;
	}
	
	
	
			void Hex::play(Location myLocation)																// plays given Location to the board
			{
				steps++;
				if(playerTurn == 1)																			// if playing for user 1
					{
						matrix[myLocation.get_x()][myLocation.get_y()].setState(CellState::user1);			// changes the cell state 
						lastLocationOfUser1 = myLocation;
						if (firstLocationOfUser1.get_x() == -1)												// if it is first Location (if it is initial value)
					firstLocationOfUser1 = myLocation;
					}
				else if(playerTurn == 2)																	// if playing for user 2 
					{
						lastLocationOfUser2 = myLocation;
						matrix[myLocation.get_x()][myLocation.get_y()].setState(CellState::user2); 			// changes the cell state 							
					}

				evaluateScore(playerTurn);
				fName = ( to_string( gameNow) + "step" + to_string(steps));
				isFinished = isGameEnded();
				if(! isFinished )
					changePlayer();
				ofstream iFile("a");
				iFile << *(this);
			}			



			Location::Location()													// constructor of Location
			{
				setLocation(-1, -1);
			}

			Location::Location(int x, int y)												// another constructor of Location
			{
				Location newLocation;
				newLocation.setLocation(x, y);
			}

			inline int Location::get_x()const	{	return x;	}

			void Location::set_y(int y_)
			{
				if (y_ < -2 || y_ > MAX_BOARD_SIZE)
					throw exception("set_y  out of exception.");
				else
					y = y_;	}

			void Location::setByAdding(int x_, int y_)									// sets the own location by adding
			{
				if ( x_+ x < -2 || x+x_ > MAX_BOARD_SIZE || y_ + y < -2 || y + y_ > MAX_BOARD_SIZE)
					throw exception("set_by_adding  out of exception.");
				else
				{
					x += x_;
					y += y_;
				}
			}

			bool Location::operator==(Location another)const									// operator== overloading for Location class
			{
				return (x == another.get_x() && y == another.get_y());
			}

			inline int Location::get_y() const{		return y;	}

			void Location::set_x(int x_)
			{	
				if (x_ < -2 || x_ > MAX_BOARD_SIZE)
					throw exception("set_x  out of exception.");
				else
					x = x_;		
			}

			Location Location::changeLocation(int x_,int y_)								// creates a new location according to parameters and old location  
			{
				Location newLocation;
				newLocation.set_x(x+x_);
				newLocation.set_y(y+y_);
				return newLocation;
			}
	
			bool Hex::isLocationCorrect(const Location myLocation)												// check if given Location is correct (if its on the matrix or not)
			{
				if(myLocation.get_x() >= boardSize || myLocation.get_y() >= boardSize || myLocation.get_x() < 0 || myLocation.get_y() < 0)
					return false;
				return true;
			}
			
		    list<Location> Hex::findConnections(Location myLocation)			// finds the Locations around a Location (neighbours)
			{
				list <Location> connections;
				connections.push_back(myLocation);
				connections.push_back( myLocation.changeLocation(-1,0) ); 
				connections.push_back( myLocation.changeLocation(1,0) );	
				connections.push_back( myLocation.changeLocation(0,-1) ); 
				connections.push_back( myLocation.changeLocation(0,1) ); 
				connections.push_back( myLocation.changeLocation(-1,1) );
				connections.push_back( myLocation.changeLocation(1,-1) );
													
				for(auto it=connections.begin(); it != connections.end();it++)
					if( !isLocationCorrect(*it) )
							connections.erase(it--);
						
				return connections;
			}			
			
			
			Location Hex::takeLocation()																	// takes a Location or commands from the user
			{
				bool flag = true;
				try{

					string PlayerNow = user2;
					if( playerTurn == 1 )
						PlayerNow = user1;

					decltype(PlayerNow) stringLocation ;

					cout << PlayerNow << " please make a move or write a command: ";
					getline(cin,stringLocation);
					stringLocation[0] = toupper(stringLocation[0]);
					
					if (stringLocation.substr(0, 4) == "UNDO")									// if user enters UNDO command
					{
						int undo = 1;															// some validation for  user input
						if ((stringLocation.length() == 6 && isdigit(stringLocation[5])) || (stringLocation.length() == 7 && isdigit(stringLocation[5]) && isdigit(stringLocation[6])) )
							undo = stringLocation[5] -'0';
							for (int i = 0; i <undo ; i++)
							{
								if (steps > 0)
								{
									steps--;
									(*this)--;																	// if user enters UNDO then the game is converted to previous one 
								}
							}
							if (undo % 2 == 1 && user2 == DEFAULT_NAME)
								cout << DEFAULT_NAME << " played again.";
						flag = false;
					}

					if( stringLocation.substr(0,4) == "LOAD" )										// if user enters LOAD command, then it loads given file
						{
							if(stringLocation[4] != ' ' )
								{
									cerr << "Please put a white space after the LOAD command !!\n";									// some validation for input
									return takeLocation();
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for loading !!\n";
											return takeLocation();
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);
									
									ifstream loadFile(stringLocation);
									loadFile >> *this;
									//	loadSavedGame(stringLocation) ;
									return takeLocation();
								}
						}
					if( stringLocation.substr(0,4) == "SAVE" )										// if user enters SAVE command, then it saves the game
						{
							if(stringLocation[4] != ' ' )
								{
									cerr << "Please put a white space after the SAVE command !!\n";					// some valdiations algorithms
									return takeLocation();
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for saving !!\n";
											return takeLocation();
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);	
									ofstream iFile("a");
									fName = stringLocation;
									iFile << *(this);
									return takeLocation();
								}
						}
					Location myLocation;
					if (stringLocation.substr(0, 3) == "NEW" && stringLocation.size() == 3)					// if user want to a new game
					{
						cout << "Press enter to start new game";
						newGame = true;
						flag = false;
					}

					if (stringLocation.substr(0, 5) == "GAME " )											// if user want to play another game
					{
						gameNow = stringLocation[5] - '0';
						flag = false;
					}

					if (stringLocation.substr(0, 8) == "COMPARE " && (stringLocation[8] - '0') < 10 && (stringLocation[10] - '0') < 10 && stringLocation[9] == ' ')			// if user want to compare two game
					{
						compare1 = stringLocation[8] -'0';
						compare2 = stringLocation[10] - '0';
						flag = false;
					}

														// these codes for input to location object

					if(!isdigit(stringLocation[1]) )							// if is there any problem with taken location 
						throw 20;

					
					myLocation.set_x( stoi(stringLocation.substr(1,stringLocation.size()-1)) -1);
					myLocation.set_y(stringLocation[0] - 'A' );	

					if( ! isLocationCorrect(myLocation))					
						throw 20;

					return myLocation;
						
					}

				catch(int e){
					if (flag)
					{
						cerr << "\nYou entered wrong number !!!\n";
						return takeLocation();
					}
				}
				return Location(-1, -1);
			}
			
			
			void Hex::changePlayer()												// changes the player now
			{
				if( playerTurn == 1 )
					playerTurn = 2;
				else
					playerTurn = 1;
			}
			
			
				bool Hex::isOnOwnBorder(Location myLocation){											// if the location is on his own borders
				if(matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::user1)
					if(myLocation.get_x() == 0 || myLocation.get_x() == boardSize-1)
						return true;
				if(matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::user2)
					if(myLocation.get_y() == 0 || myLocation.get_y() == boardSize-1)
						return true;
				return false;
			}

			bool Hex::isUserLocationOwner(Location myLocation){																	// check if the user is Location owner
				short owner = 0;																								
				char locationValue = owner = char(matrix[myLocation.get_x()][myLocation.get_y()].getCellState());
				if(locationValue == CellState::user1)
					owner = 1;
				else if(locationValue == CellState::user2)
					owner = 2;
				
				return owner == playerTurn ? true : false; 
				
			}

			void Hex::operator==(Hex& other)																		// to control which hex object has more marked cells
			{
					if ((*this).isMarkedCellsMore(other))
						cout << endl << compare1 << " has more marked cells than " << compare2 << endl;
					else
						cout << endl << compare2 << " has more marked cells than " << compare1 << endl;
			}

			void Hex::deleteTheTempFiles()
			{
				for (int i = 0; i <= steps; i++)
				{
					string fileName = to_string(gameNow) + "step" + to_string(i);
					remove(fileName.c_str());
				}
			}
			
			
			void Hex::showResults()												// shows which user is winner and shows the point
			{
				int scr;
				if (playerTurn == 1)
				{
					winner = this->user1;
					scr = score1;
				}
					
				else
				{
					winner = this->user2;
					scr = score2;
				}
				scr += 100;					

				cout << *this;
				cout << "\n\n !!!!!  " << winner << "  is winner. Your points " << scr << " Congratulations  !!!!!\n\n\n\n";
			}
			

		
			bool operator >> (std::ifstream& inputStream, Hex& game)										// for loading saved game
			{
				if(inputStream.fail())
				{
					cout << game;
					cerr << endl << "The file is not found\n";				// if the given file name is not found gives an error to the user.
					return false;
				}
				else
				{
					inputStream >> game.boardSize >> game.steps								// if file name is found then start to copy the values row by row.
					>> game.user1 >> game.user2 ;							// each row is for one variable or array
					inputStream.get();
					for (int i = 0; i < game.boardSize; i++)									// saves the matrix
					{
						for (int j = 0; j < game.boardSize; j++)
							game.matrix[i][j].setState( inputStream.get() );
					}
					inputStream.get();
					
					inputStream >> game.isFinished;
					inputStream >> game.playerTurn
						>> game.lastLocationOfUser1													// saves variables
						>> game.lastLocationOfUser2
						>> game.firstLocationOfUser1
						>> game.firstLocationOfUser2;
					

					short mvm1,mvm2;
					inputStream >> mvm1 >> mvm2 ;
					game.lastMovementOfUser1 = (Movement)mvm1;
					game.lastMovementOfUser2 = (Movement)mvm2;

					inputStream.close();
					cout << game;
					cout << "\nThe file loaded successfully\n";							// if the loading is successcfull then gives an output to the user.
					return true;

				}
			
			}
			
			
			
			bool Hex::saveGame(string fileName)								// this function is private call it only from operator<< (for saving and displaying)  To save the game and all variables and arrays etc. this 
			{
				ifstream inputStream(fileName.c_str());
				if(!inputStream.fail() && fileName.substr(1,4) !="step" )														// checks if there is a file with given string
				{
					cerr << "\nThere is a file with this name please try another name ";	// if it find a file with given string then it gives an error to try again.
					inputStream.close();
					return false;
				}
				else															// if there is no problem about file name then starts to save information row by row.
				{
					inputStream.close();
					ofstream outputStream(fileName.c_str());

					outputStream << boardSize << ' ' << steps <<endl
					<< user1 << ' ' << user2 << endl;
					
					for (int i = 0; i < boardSize; i++)												// saves the matrix array 
					{
						for (int j = 0; j < boardSize; j++)
							outputStream << char( (matrix[i][j]).getCellState());	
					}

					outputStream << endl << isFinished << endl		
					<< playerTurn << endl
					<< lastLocationOfUser1.get_x() << ' ' << lastLocationOfUser1.get_y() << ' '
					<< lastLocationOfUser2.get_x() << ' ' << firstLocationOfUser2.get_y() << ' '
					<< firstLocationOfUser1.get_x() <<' '<< firstLocationOfUser1.get_y() << ' '
					<< firstLocationOfUser2.get_x() <<' '<< firstLocationOfUser2.get_y() << ' ' << endl; 
					
					outputStream << int(';') << endl << lastMovementOfUser1 << ' ' << lastMovementOfUser2 ;

					outputStream.close();
					cout << "The game saved successfully\n";
					return true;	
				}

			}
			
	Location Hex::goAhead(Movement myMovement,Location fromThis){							// gives the location depends on movement from a location
				decltype(fromThis) newLocation = fromThis;
				short mv = myMovement;
				switch(mv){
					case up: newLocation.setByAdding(-2, 1); break;
					case down: newLocation.setByAdding(2, -1); break;
					case rght: newLocation.setByAdding(0, 1); break;
					case lft: newLocation.setByAdding(0, -1); break;
					case up_left: newLocation.setByAdding(-1, 0); break;
					case up_rght: newLocation.setByAdding(-1, 1); break;
					case down_right:newLocation.setByAdding(1, 0);break;
					case down_left: newLocation.setByAdding(1, -1);break;
				}
				return newLocation;
			}

			Location Hex::firstMovement(){												// if this Movement is first Movement selects a locaton.
				random_device random;						
				mt19937 gen(random());
				Location myLocation;
				short middle = boardSize /2;
				uniform_int_distribution<> distr(0,middle-1);
																								// looks which side is used by the other user 
				if (lastLocationOfUser1.get_y() > middle-1 )
					myLocation.set_y(lastLocationOfUser1.get_y() - distr(gen));
				else
					myLocation.set_y(distr(gen));
				int difference = lastLocationOfUser1.get_y() - myLocation.get_y();
				myLocation.set_x(lastLocationOfUser1.get_x() + (difference < 0 ? -1*difference  : difference)*(2.0/3.0) );
				if(!isLocationCorrect(myLocation) || !isLocationEmpty(myLocation) || myLocation.get_x() == boardSize-1 )
					return firstMovement();
				firstLocationOfUser2 = myLocation;
				return myLocation;
			}

            bool Hex::isContainsDirection(list<Movement> directions, Movement direction)				// finds if given list has given direction or not
			{
				for(auto m : directions)					// burası da
				{
					if(direction == m)
					return true;
				}
				return false;
			}


            Location Hex::move()				// gives a Location for playing
			{
				vector<Cell> freeCells;
				for (int i = 0; i < this->getBoardSize(); i++)
					for (int j = 0; j < this->getBoardSize(); j++)
						if (matrix[i][j].getCellState() == CellState::dot)
							freeCells.push_back(matrix[i][j]);
				

				default_random_engine defEngine;
				uniform_int_distribution<int> intDistro(0, freeCells.size());

				int randomIndex = intDistro(defEngine);
				
				return freeCells.at(randomIndex).getLocation();
			}

            list<Location> Hex::findConnections(Location myLocation,short boardSize)			// finds the Locations around a Location 
			{
				list <Location> connections;
				connections.push_back(myLocation);
				connections.push_back( myLocation.changeLocation(-1,0) ); 
				connections.push_back( myLocation.changeLocation(1,0) );	
				connections.push_back( myLocation.changeLocation(0,-1) ); 
				connections.push_back( myLocation.changeLocation(0,1) ); 
				connections.push_back( myLocation.changeLocation(-1,1) );
				connections.push_back( myLocation.changeLocation(1,-1) );
													
				for(auto it=connections.begin(); it != connections.end();it++)
					if( !isLocationCorrect(*it) )
							connections.erase(it--);
						
				return connections;
			}

			bool Hex::evaluateScore(short user)
			{
				if (user == 1)
				{
					if (isOnOwnBorder(lastLocationOfUser1))
					{
						bool flag = false;
						for (int i = 0; i < boardSize; i++)				// if last location is on border
							if (matrix[lastLocationOfUser1.get_x()][i].getCellState() == CellState::user1)
							{
								score1 += 10;
								flag = true;
							}
						if(!flag)
						score1 += 30;
					}


					for (int i = 0; i < boardSize; i++)				// if last location of user 1 aproaches to the border
						if (matrix[lastLocationOfUser1.get_x()][i].getCellState() == CellState::user1)
						{
							score1 += 3;
							return true;
						}

					score1 += 5;
					return true;
				}

				else if (user == 2)
				{

					if (isOnOwnBorder(lastLocationOfUser2))
					{
						bool flag = false;
						for (int i = 0; i < boardSize; i++)				// if last location of user 2 aproaches to the border
							if (matrix[i][lastLocationOfUser2.get_y()].getCellState() == CellState::user2)
							{
								score1 += 10;
								flag = true;
							}
						if (!flag)
							score1 += 30;
					}



					for (int i = 0; i < boardSize; i++)				// if last location of user 2 aproaches to the border
						if (matrix[i][lastLocationOfUser2.get_y()].getCellState() == CellState::user2)
						{
							score2 += 3;
							return true;
						}

					score2 += 5;
					return true;

				}
				else
					return false;

			}

			Hex Hex::operator--()													// pre decreament operator overloading for hex class (undo) (goes to previous )
			{
				string s = to_string(gameNow) +"step" + to_string(steps);			
				Hex old = *this;
				ifstream loadFile(s);
				loadFile >> *this;
				return old;
			}

			Hex& Hex::operator--(int i)												// post decreament operator overloading for hex class (undo) (goes to previous )
			{
				string s = to_string(gameNow) + "step" + to_string(steps);
			
				ifstream loadFile(s);
				loadFile >> *this;
				//	loadSavedGame( s );
				return *this;
			}
			

			bool Hex::pTest(Location current, std::list<Location> & scannedLocations)			// for testing if current user is completed the path from the location
			{										
				CellState state;
				Location lastBorder;
				if(playerTurn == 1)
				{
					state = CellState::user1;
					lastBorder.setLocation(-1, boardSize - 1);								// sets the last border if user 1 and 2
				}

				if (playerTurn == 2)
				{
					state = CellState::user2;
					lastBorder.setLocation(boardSize-1,-1);
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
						if (isLocationCorrect(x) && isUserLocationOwner(x) )
							if( pTest(x,scannedLocations))
								return true;
					}
					
				}
				return false;
			}

			bool Hex::isGameEnded()													// checks if is there any path that connects the borders
			{
				
				Location loc;
				loc.set_x(0);
				loc.set_y(0);
				list<Location> scannedLocations;
				if (playerTurn == 2)										// if player is 2 
				{
					for (int j = 0; j < boardSize-1; j++)						// checks all first border of user 2
					{
						loc.set_y(j);
						if (pTest(loc,scannedLocations))										// if path is found to the last border
							return true;
					}		
					return false;
				}
				else 											// if player is 1
				{
					for (int i = 0; i < boardSize-1; i++)						// checks all location of first border one by one
					{
						loc.set_x(i);
						if (pTest(loc,scannedLocations))										// if path is found to the last border
							return true;
					}		
					return false;
				}

			}



			std::istream& operator>>(std::istream& in, Location location)
			{
				int a, b;
				in >> a;
				in >> b;
				location.set_x(a);
				location.set_y(b);
				return in;
			}


			Hex::Cell::Cell(int x, int y, CellState state)
				{
					location.setLocation(x, y);
					cellState = state;
				}

			Hex::Cell::Cell()
			{
				Cell(0, 0, CellState::dot);
			}

			Location Hex::Cell::getLocation()
			{
				return this->location;
			}
			
			Hex::CellMatrix::CellMatrix(int boardSize)			// constructor of CellMatrix class
			{
				
					if (boardSize > 25 || boardSize < 0)
						cout << "boardSize must be between 0 and 25";
					else
					{
						matrix = new row[boardSize];
						for (int i = 0; i < boardSize; ++i)
						{
							matrix[i] = new Cell[boardSize];
							for (int j = 0; j < boardSize; ++j)
							{
								matrix[i][j].setLocation(i, j);
								matrix[i][j].setState(CellState::dot);
							}
						}
						size = boardSize;
					}
				
				
			}
			Hex::CellMatrix::CellMatrix()
			{
				matrix = nullptr;
				size = 0;
			}

			Hex::CellMatrix::CellMatrix(const CellMatrix& other)				// copy constructor of CellMatrix class
			{
					if (this->size != other.size)
					{
						//		delete[] matrix;
						if (other.getSize() < 25 && other.getSize() > 0)
							matrix = new row[other.getSize()];
						size = other.getSize();
					}
					for (int i = 0; i < other.getSize(); i++)
					{
						matrix[i] = new Cell[other.getSize()];
						for (int j = 0; j < other.getSize(); j++)
						{
							matrix[i][j].setLocation(i, j);
							matrix[i][j].setState(other.matrix[i][j].getCellState());
						}
					}
			}

			int Hex::CellMatrix::getSize() const	{	return size;	}

			Hex::CellMatrix & Hex::CellMatrix::operator= (CellMatrix rValue)			// assignment operator overloading for Hex class
			{
					if (rValue.size > 25 && rValue.size < 6)
					{
						while (1)
							cout << "should be between 6-25";
						return *this;
					}
					else
					{
						if (this->size != rValue.size)
						{
							delete[] matrix;
							matrix = new row[rValue.getSize()];
						}
						for (int i = 0; i < rValue.getSize(); i++)
						{
							matrix[i] = new Cell[rValue.getSize()];
							for (int j = 0; j < rValue.getSize(); j++)
							{
								matrix[i][j] = rValue.matrix[i][j];
							}
						}
						size = rValue.size;
						return *this;
					}
			}

			Hex::CellMatrix::~CellMatrix()							// destructor of Cellmatrix class
			{
				if (matrix != nullptr)
				{
					for (int i = 0; i < size; ++i)
						delete[] matrix[i];
					delete[] matrix;
				}
			}
