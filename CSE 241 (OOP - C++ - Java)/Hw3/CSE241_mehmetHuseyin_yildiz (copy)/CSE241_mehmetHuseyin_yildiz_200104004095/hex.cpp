#include"hex.h"
#include<iostream>
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
	int Hex::MarkedCellsOfAllBoards(vector<Hex> & hexGames)								// return numbers of all boards (static function)
	{
		int sum = 0;
		for (Hex hexGame : hexGames)
			sum += hexGame.numberOfMarkedCells();
		return sum;
	}

	bool Hex::isLocationEmpty(Location myLocation)
	{
		if (!isLocationCorrect(myLocation))
			return false;
				if( matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::dot)
					return true;
				return false;				
	}	
	
	
	void Hex::createMatrix()
	{
			for (int i = 0; i < boardSize ; ++i)
				{
					vector<Cell> row;
					for (int j = 0; j < boardSize; ++j)
						{
							Cell newCell(i,j,CellState::dot);							
							row.push_back(newCell);
						}
					matrix.push_back(row);
				}
	}

	


	void Hex::PlayGame()
	{
	//	while (!isFinished) {													// the game keeps going while the game is not finished.
			display();																								// displays the board after every playing.
			try {
				//	int locationSize = hexGame.boardSize * hexGame.boardSize /2;
				Location myLocation;
				Moving myMoving;

				if (getPlayerTurn() == 1 || user2 != DEFAULT_NAME) 					// sıra user 1 de veya ikili oynanırken
				{
					myLocation = takeLocation();

					if (isLocationCorrect(myLocation) && isLocationEmpty(myLocation))
						play(myLocation);

					else
					{
						cerr << "You entered wrong location please enter again\n";
					}
				}
				else																			// if the player is computer
					play();
				
				if(isGameEnded())
					showResults();
				else
					changePlayer();														// changes the user now at last.
			}
			catch (int e) {
				if (e == 20)
					cerr << "You entered wrong location please enter it again";
				else
					cerr << "There is unknown error";
			}

			display();
		}

	//	showResults();												// shows the winner

	//}

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
				cout<<"Enter board size Please (Like:7x7): ";			// takes board size
				string a;
				getline(cin,a);
				
				if (a.size() == 3)
				{
					if ((a[0] - '0') < 0 || a[1] != 'x' || a[2] - '0' > 26 || a[0] != a[2])
					{
						cout << "!!! Wrong format please try again: ";
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
				
				
				if (selection <= 5)
				{
					cout << selection << " is too short. Press Enter to enter again: ";
					goto boardSize;
				}
				else
					boardSize = selection;
				
                createMatrix();

			}

			void Hex::play()
			{
				Location myLocation;
				Moving myMoving;

				if (firstLocationOfUser2.get_x() == -1)						// ilk oynayÄ±ÅŸÄ± ise
					myLocation = firstMovement();
				else
				{
					myMoving = move();
					myLocation = myMoving.locationAfter;
				}
				if (!isLocationCorrect(myLocation) || !isLocationEmpty(myLocation))
					play();
				else
				{
					if (!myMoving.isItBridging)												// normal ilerleme ise
					{
						lastLocationOfUser2 = myLocation;
						lastMovementOfUser2 = myMoving.direction;
						play(myLocation);
					}
					else																	// ara noktalarÄ± dolduruyorsa
						play(myLocation);

				}
			}

			int Hex::getWidth()
			{
				return boardSize*3 -1;
			}

			int Hex::getHeight()
			{
				return boardSize;
			}
	
		void Hex::display()										// displays the last situation of the board				
			{
				cout << "  ";
				for (int letter = 0; letter < boardSize; letter++)
					cout << char('a' + letter) <<' ';
				cout << endl;
				for(int i = 0; i<boardSize; i++)
				{
					cout << i+1<<' ';
					for(int space=0; space< (i>8?i-1:i); space++)
						cout<<" ";
						
					for(int j=0; j<boardSize; j++ )
					{
						cout<< char(matrix[i][j].getCellState())<<" ";
					}
					cout<<"\n";
				}
			}
			
	void Hex::clearScreen()
	{														// clears the screen
				cout << "\033[2J\033[1;1H";
	}

	int Hex::numberOfMarkedCells()							// it return number of marked cells of the object. There is also static function that returns number of markeds for all boards.
	{
		int sum = 0;
		for(auto row:matrix)
			for (auto cell : row)
			{
				if (cell.getCellState() == CellState::user1 || cell.getCellState() == CellState::user2)
					sum++;
			}
		return sum;
	}
	
	
	
			void Hex::play(Location myLocation)							// plays given Location to the board
			{

				if(playerTurn == 1)
					{
						matrix[myLocation.get_x()][myLocation.get_y()].setState(CellState::user1);  
						lastLocationOfUser1 = myLocation;
						if (firstLocationOfUser1.get_x() == -1)
					firstLocationOfUser1 = myLocation;
					}
				else if(playerTurn == 2)
					{
					lastLocationOfUser2 = myLocation;
						matrix[myLocation.get_x()][myLocation.get_y()].setState(CellState::user2); 										// bilgisayar implementasyonu eksik
						
					}

				
			}			



			Location::Location()
			{
				setLocation(-1, -1);
			}

			Location::Location(int x, int y)
			{
				Location newLocation;
				newLocation.setLocation(x, y);
			}

			inline int Location::get_x()const
			{
				return x;
			}

			void Location::set_y(int y_)
			{
				y = y_;
			}

			void Location::setByAdding(int x_, int y_)
			{
				x += x_;
				y += y_;
			}

			bool Location::operator==(Location another)const
			{
				return (x == another.get_x() && y == another.get_y());
			}

			inline int Location::get_y() const
			{
				return y;
			}

			void Location::set_x(int x_)
			{
				x = x_;
			}

			Location Location::changeLocation(int x_,int y_)
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

			//Hex::displayAllGames(vector<Hex> games)
			//{
			//	int maxwidth = 60, sumWidth=0, matrixNumberInRow= games.size();
			//	int maxHeight = 6;

			//	for(int i=0; i<maxHeight; i++)
			//	{
			//		for (int j=0; j<matrixNumberInRow; j++)
			//		{
			//			if (maxHeight < games[j].getHeight())
			//				maxHeight = games[j].getHeight();

			//			sumWidth += games[i].getWidth();

			//			for(auto cell :games[j].matrix[i])												// matrixin bir row'unu ekrana basar
			//			{
			//				for()
			//				{
			//					cell.															// boşuk bas
			//				}
			//				cout << char(cell.getCellState()) << ' ';
			//			}

			//			if (sumWidth + games[i + 1].getWidth() >= maxwidth)
			//				matrixNumberInRow = j+1;
			//		}
			//	}
			//}
			
           
		    list<Location> Hex::findConnections(Location myLocation)			// finds the Locations around a Location 
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
			
			
			Location Hex::takeLocation()																				// takes a Location or SAVE-LOAD command from the user
			{
				
				try{

					string PlayerNow = user2;
					if( playerTurn == 1 )
						PlayerNow = user1;

					decltype(PlayerNow) stringLocation ;

					cout << PlayerNow << " please make a move or write a command: ";
				//	cin.clear();
				//	cin.ignore(100,'\n');
					getline(cin,stringLocation);
					stringLocation[0] = toupper(stringLocation[0]);
					if( stringLocation.substr(0,4) == "LOAD" )										// if user enters LOAD command, then it loads given file
						{
							if(stringLocation[4] != ' ' )
								{
									cerr << "Please put a white space after the LOAD command !!\n";
									return takeLocation();
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for loading !!\n";
											return takeLocation();
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);
									loadSavedGame(stringLocation) ;
									return takeLocation();
								}
						}
					if( stringLocation.substr(0,4) == "SAVE" )										// if user enters SAVE command, then it saves the game
						{
							if(stringLocation[4] != ' ' )
								{
									cerr << "Please put a white space after the SAVE command !!\n";
									return takeLocation();
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for saving !!\n";
											return takeLocation();
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);	
									saveGame(stringLocation) ;
									return takeLocation();
								}
						}
					Location myLocation;
					if (stringLocation.substr(0, 3) == "NEW" && stringLocation.size() == 3)
					{
						cout << "Press enter to start new game";
						newGame = true;
						return myLocation;
					}

					if (stringLocation.substr(0, 5) == "GAME " )
					{
						gameNow = stringLocation[5] - '0';
						return myLocation;
					}

					if (stringLocation.substr(0, 8) == "COMPARE " && (stringLocation[8] - '0') < 10 && (stringLocation[10] - '0') < 10 && stringLocation[9] == ' ')
					{
						compare1 = stringLocation[9] -'0';
						compare2 = stringLocation[11] - '0';
						return myLocation;
					}

					if(!isdigit(stringLocation[1]) )
						throw 20;

					
					myLocation.set_x( stoi(stringLocation.substr(1,stringLocation.size()-1)) -1);
					myLocation.set_y(stringLocation[0] - 'A' );	

					if( ! isLocationCorrect(myLocation))
						throw 20;

					return myLocation;
						
					}

				catch(int e){
					cerr << "\nYou entered wrong number !!!\n";
					return takeLocation();
				}

			}
			
				bool Hex::isInScanned(const Location myLocation,const vector<Location> scannedLocations ){
				for(auto i:scannedLocations){
						if ( i == myLocation)																							// !!!!! operator overloading
						return true;
					}
				return false;	
			}	
			
			
			void Hex::changePlayer()												// changes the player now
			{
				if( playerTurn == 1 )
					playerTurn = 2;
				else
					playerTurn = 1;
			}
			
			
			bool Hex::isBordersConnected(vector<Location> scannedLocations)
			{			
				bool isBorder1Connected=false, isBorder2Connected = false;
				int i = 0;

				if(playerTurn == 2)
					for(auto i:scannedLocations)												//default Location değerine eşit olmayınca arar
					{
						if(i.get_x() == 0)
							isBorder1Connected = true;
						else if( i.get_x() == boardSize-1  )
							isBorder2Connected = true;
					}

				else if(playerTurn == 1)
					for (auto i : scannedLocations)												//default Location değerine eşit olmayınca arar
					{
						if(i.get_y() == 0)
							isBorder1Connected = true;
						else if( i.get_y() == boardSize-1  )
							isBorder2Connected = true;
					}
				
				return isBorder1Connected && isBorder2Connected ? true : false;															
				
			}

			
			
			
			bool Hex::isPathCompleted (Location myLocation, vector<Location> & scannedLocations)			// checks if Path is completed or not
			{
				
				list<Location> connections = findConnections(myLocation);
		//		list<location>::iterator it;																			
				for( auto it : connections)
				{	
					if(isLocationCorrect(it) && isUserLocationOwner(it) )
					{
						if (isInScanned(it, scannedLocations) )
							continue;
						else
							{
							scannedLocations.push_back(it);
								isPathCompleted(it,scannedLocations);
							}
					}
				}
				if( isBordersConnected(scannedLocations ) )
							{
								for(auto i:scannedLocations)
									matrix[i.get_x()][i.get_y()].setState(  getStateForPlayerNow() + 'A' -'a'    );
								
								return true;
							}
				return false ;
			}
			
			
			
			
			
			
				bool Hex::isOnOwnBorder(Location myLocation){							// aldığı konumun kendi sınırlarında olup olmadığını bulur.
				if(matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::user1)
					if(myLocation.get_x() == 0 || myLocation.get_x() == boardSize-1)
						return true;
				if(matrix[myLocation.get_x()][myLocation.get_y()].getCellState() == CellState::user2)
					if(myLocation.get_y() == 0 || myLocation.get_y() == boardSize-1)
						return true;
				return false;
			}

			bool Hex::isUserLocationOwner(Location myLocation){
				short owner = 0;																								// sıfır ise sahipsiz
				char locationValue = owner = char(matrix[myLocation.get_x()][myLocation.get_y()].getCellState());
				if(locationValue == CellState::user1)
					owner = 1;
				else if(locationValue == CellState::user2)
					owner = 2;
				
				return owner == playerTurn ? true : false; 
				
			}



			void Hex::addToScannedLocations(Location newLocation, vector<Location> scannedLocations)
			{
					
			}
			
			
			
			
			
			
			void Hex::showResults()												// shows which user is winner
			{								
				display();
				cout << "\n\n !!!!!  " << winner << "  is winner, Congratulations  !!!!!\n";
			}
			
			
			
		
		
			bool Hex::loadSavedGame(string fileName)									// loads the saved game
			{
				ifstream inputStream(fileName.c_str());
				if(inputStream.fail())
				{
					display();
					cerr << endl << fileName << " is not found\n";				// if the given file name is not found gives an error to the user.
					return false;
				}
				else
				{
					inputStream >> boardSize								// if file name is found then start to copy the values row by row.
					>> user1 >> user2 ;							// each row is for one variable or array
					inputStream.get();
					for (int i = 0; i < boardSize; i++)									// matrix kaydedilir
					{
						for (int j = 0; j < boardSize; j++)
							matrix[i][j].setState( inputStream.get() );
					}
					inputStream.get();
					
					inputStream >> isFinished;
						inputStream>> playerTurn
					>> lastLocationOfUser1
					>> lastLocationOfUser2
					>> firstLocationOfUser1
					>> firstLocationOfUser2 
					
					>> bridges;															// made with operator overloading 

					short mvm1,mvm2;
					inputStream >> mvm1 >> mvm2 ;
					lastMovementOfUser1 = (Movement)mvm1;
					lastMovementOfUser2 = (Movement)mvm2;

					inputStream.close();
					display();
					cout << "\nThe file loaded successfully\n";							// if the loading is successcfull then gives an output to the user.
					return true;

				}
			
			}
			
			
			
			bool Hex::saveGame(string fileName)								// To save the game and all variables and arrays etc.
			{
				ifstream inputStream(fileName.c_str());
				if(!inputStream.fail())														// checks if there is a file with given string
				{
					cerr << "\nThere is a file with this name please try another name ";	// if it find a file with given string then it gives an error to try again.
					inputStream.close();
					return false;
				}
				else															// if there is no problem about file name then starts to save information row by row.
				{
					inputStream.close();
					ofstream outputStream(fileName.c_str());

					outputStream << boardSize << endl
					<< user1 << ' ' << user2 << endl;
					
					for (int i = 0; i < boardSize; i++)									// saves the matrix array 
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
					
					for(auto bridgeTosave : bridges)										// saves the bridges
					{
						outputStream << bridgeTosave.left.get_x() <<' '<< bridgeTosave.left.get_y() << ' '
						<< bridgeTosave.right.get_x() << ' ' << bridgeTosave.right.get_y() << ' ';
					}

					outputStream << int(';') << endl << lastMovementOfUser1 << ' ' << lastMovementOfUser2 ;

					outputStream.close();
					cout << "The game saved successfully\n";
					return true;	
				}

			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	

	Location Hex::goAhead(Movement myMovement,Location fromThis){							// belirtilen lokasyondan istenilen yönün lokasyonunu döndürür.
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

			Bridge Hex::findBridge(const Location loc1,const Location loc2){									// finds a Bridge (points between two point)
				Bridge myBridge;
				if( goAhead(up,loc1) == loc2 )
				{

					myBridge.right.setLocation(loc2.get_x()+1, loc2.get_y());

					//myBridge.left.set_y(loc1.get_y();
					//myBridge.left.set_x(loc1.get_x() -1; 
					
					myBridge.left.setLocation(loc1.get_x()-1, loc1.get_y() );

				}
				if(loc2 == goAhead(down, loc1))
				{
					//myBridge.right.set_y(loc1.get_y();
					//myBridge.right.set_x(loc1.get_x() +1;

					myBridge.right.setLocation(loc1.get_x()+1, loc1.get_y());

					//myBridge.left.set_y(loc2.get_y();
					//myBridge.left.set_x(loc1.get_x() -1;

					myBridge.left.setLocation(loc1.get_x() - 1, loc2.get_y());

				}
				if(loc2 == goAhead(up_2nd_right, loc1))
				{
					//myBridge.right.set_y(loc1.get_y() +1;
					//myBridge.right.set_x(loc1.get_x();

					myBridge.right.setLocation(loc1.get_x(), loc1.get_y()+1 );


					//myBridge.left.set_y(loc1.get_y() +1;
					//myBridge.left.set_x(loc2.get_x();
				
					myBridge.left.setLocation(loc2.get_x(), loc1.get_y() +1);

				}
				if(loc2 == goAhead(up_2nd_left, loc1))
				{
					//myBridge.right.set_y(loc1.get_y();
					//myBridge.right.set_x(loc2.get_x();

					myBridge.right.setLocation(loc2.get_x(), loc1.get_y());


					//myBridge.left.set_y(loc2.get_y();
					//myBridge.left.set_x(loc1.get_y();

					myBridge.left.setLocation(loc1.get_y() , loc2.get_y());

				}
				if(loc2 == goAhead(down_2nd_right, loc1) )
				{
					//myBridge.right.set_y(loc2.get_y();
					//myBridge.right.set_x(loc1.get_x();

					myBridge.right.setLocation(loc1.get_x(), loc2.get_y());


					//myBridge.left.set_y(loc1.get_y();
					//myBridge.left.set_x(loc2.get_x();

					myBridge.left.setLocation(loc2.get_x(), loc1.get_y());

				}
				return myBridge;
			}

            Moving Hex::move()				// gives a Location for playing
			{
				Location myLocation;
				Bridge myBridge;
				Moving myMoving;
				//	list<bridge>::iterator it;
				myMoving.locationBefore = lastLocationOfUser2;

				if (bridges.size() > 0)
					for (auto it = bridges.begin(); it != bridges.end(); it++)				// bridge lerden biri dolunursa diÄŸerini alÄ±r.
					{
						if (matrix[(*it).left.get_x()][(*it).left.get_y()].getCellState() == CellState::user1)
						{
							myLocation.set_x((*it).right.get_x());
							myLocation.set_y((*it).right.get_y());
							myMoving.locationAfter = myLocation;
							myMoving.isItBridging = true;
							bridges.erase(it);

							return myMoving;
						}
						if (matrix[(*it).right.get_x() ][(*it).right.get_y() ].getCellState() == CellState::user1) {
							myLocation.set_x((*it).left.get_x());
							myLocation.set_y((*it).left.get_y() );
							myMoving.locationAfter = myLocation;
							myMoving.isItBridging = true;
							bridges.erase(it);

							return myMoving;
						}
					}

				if ((lastLocationOfUser2.get_x() >= boardSize - 2 && firstLocationOfUser2.get_x() <= 1) || (lastLocationOfUser2.get_x() <= 1 && firstLocationOfUser2.get_x() >= boardSize - 2))		// iki tarafta border a yetiÅŸirse bridge leri doldur
				{
					for (auto it = bridges.begin(); it != bridges.end(); it++) {
						if (isLocationEmpty(Bridge(*it).left))
						{
							Bridge dlt = *it;
							bridges.erase(it);
							myMoving.isItBridging = true;
							myMoving.locationAfter = dlt.left;
							return myMoving;
						}
						else
						{
							Bridge dlt = *it;
							bridges.erase(it);
							myMoving.isItBridging = true;
							myMoving.locationAfter = dlt.right;
							return myMoving;
						}

					}
				}
				if (lastLocationOfUser2.get_x() == boardSize - 2 && lastMovementOfUser2 != up)	// alt border a yetiÅŸmesine 1 adÄ±m kaldÄ±ysa diÄŸer uÃ§tan devam et.
				{

					if (myLocation.get_y()  == 0)
					{
						myMoving.direction = down_right;
						myMoving.locationAfter.set_x(boardSize - 1);
						myMoving.locationAfter.set_y(0);
						return myMoving;
					}


					decltype(myLocation) bckp = goAhead(down_left, lastLocationOfUser2);
					myBridge.left = bckp;
					bckp = goAhead(down_right, lastLocationOfUser2);
					myBridge.right = bckp;
					bridges.push_back(myBridge);

					decltype(myLocation) backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = up;								// !!!!!! buraya sonsuz dÃ¶ngÃ¼ye girmemesi iÃ§in bi ÅŸey koy bi up bi down olacak
					return move();
				}

				if (lastLocationOfUser2.get_x() == boardSize - 1 && lastMovementOfUser2 != up) {						// alt border'Ä± tamamladÄ±ysa diÄŸerine doÄŸru git
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = up;
					return move();
				}

				if (lastLocationOfUser2.get_x() == 1 && lastMovementOfUser2 != down) {					// Ã¼st border a yetiÅŸmesine 1 adÄ±m kaldÄ±ysa diÄŸer uÃ§tan devam et.

					if (myLocation.get_y()  == boardSize - 1)
					{
						myMoving.direction = up_left;
						myMoving.locationAfter.set_x(0);
						myMoving.locationAfter.set_y(boardSize - 1);
						return myMoving;
					}


					myBridge.left.set_x(0);
					myBridge.left.set_y(lastLocationOfUser2.get_y());
					myBridge.right.set_x(0);
					myBridge.right.set_y(lastLocationOfUser2.get_y() + 1);
					bridges.push_back(myBridge);
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = down;
					return move();
				}

				if (lastLocationOfUser2.get_x() == 0 && lastMovementOfUser2 != up) {						// Ã¼st border Ä± tamamladÄ±ysa diÄŸerine doÄŸru git
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = down;
					return move();
				}

				if (lastMovementOfUser2 == no) {									// yÃ¶n belirleme iÃ§in
					if (lastLocationOfUser1.get_x() <= lastLocationOfUser2.get_x() )				// son hamle rakibin hamlesinin Ã¼stÃ¼nde ise
					{
						Movement mvmnts[] = { up,up_2nd_right,up_2nd_left };
						for (auto m : mvmnts) {											// burasÄ± da
							myLocation = goAhead(m, lastLocationOfUser2);
							myBridge = findBridge(myLocation, lastLocationOfUser2);
							if (!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))			// soldaki bridge'i rakip alÄ±r ise saÄŸdakine git
							{
								if (!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right))
									continue;
								myMoving.locationAfter = myBridge.right;
								myMoving.direction = lastLocationOfUser2.get_x() > firstLocationOfUser2.get_x() ? down : up;
								return myMoving;
							}
							else if (!isLocationEmpty(myBridge.right), !isUserLocationOwner(myBridge.left))			// saÄŸdaki bridge'i rakip alÄ±r ise soldakine git
							{
								if (!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))
									continue;
								myMoving.locationAfter = myBridge.left;
								myMoving.direction = lastLocationOfUser2.get_x() > firstLocationOfUser2.get_x() ? down : up;
								return myMoving;
							}

							else if (isLocationEmpty(myLocation) && myBridge.left.get_x() != -1 && myBridge.right.get_x() != -1)
							{
								myMoving.direction = m;
								break;
							}
						}
						myMoving.locationAfter = myLocation;
					}
					else
					{
						Movement mvmnts[] = { down,down_2nd_right,down_2nd_left };
						for (auto m : mvmnts) {
							myLocation = goAhead(m, lastLocationOfUser2);
							myBridge = findBridge(myLocation, lastLocationOfUser2);
							if (isLocationEmpty(myLocation) && myBridge.left.get_x() != -1 && myBridge.right.get_x() != -1)
							{
								myMoving.direction = m;
								break;
							}
						}
						myMoving.locationAfter = myLocation;
					}
					bridges.push_back(myBridge);			// bridge kontrolu yap !!
					return myMoving;
				}

				else																							// yÃ¶n belirli ise
				{
					//	short range = 0;						// !! yukarÄ± ise
					list<Movement> upDirections = { up,up_2nd_left,up_2nd_right,up_left,up_rght,lft,rght };					// yÃ¶n sÄ±ralamasÄ±
					list<Movement> downDirections = { down,down_2nd_right,down_2nd_left,down_right,down_left,rght,lft };
					list<Movement>directions;
					if (lastMovementOfUser2 == rght || lastMovementOfUser2 == lft) {							// yÃ¶n saÄŸ veya sol ise yukarÄ± mÄ± aÅŸaÄŸÄ± mÄ± gidileceÄŸi belirlenir.
						if (lastLocationOfUser2.get_x() > firstLocationOfUser2.get_x())
							directions = downDirections;
						else
							directions = upDirections;
					}
					else
					{
						if (isContainsDirection(upDirections, lastMovementOfUser2))
							directions = upDirections;
						else
							directions = downDirections;
					}
					for (auto direction : directions)
					{
						myLocation = goAhead(Movement(direction), lastLocationOfUser2);
						if (isLocationEmpty(myLocation) && isLocationCorrect(myLocation)) {
							if (direction == up_2nd_right || direction == up_2nd_left || direction == up || direction == down || direction == down_2nd_left || direction == down_2nd_right)
							{
								myBridge = findBridge(lastLocationOfUser2, myLocation);
								if (!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))			// soldaki bridge'i rakip alÄ±r ise saÄŸdakine git
								{
									if (!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right))
										continue;
									myMoving.locationAfter = myBridge.right;
									myMoving.direction = lastLocationOfUser2.get_x() > firstLocationOfUser2.get_x() ? down : up;
									return myMoving;
								}
								if (!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right))			// saÄŸdaki bridge'i rakip alÄ±r ise soldakine git
								{
									if (!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))
										continue;
									myMoving.locationAfter = myBridge.left;
									myMoving.direction = lastLocationOfUser2.get_x() > firstLocationOfUser2.get_x() ? down : up;
									return myMoving;
								}

								if (isLocationCorrect(myBridge.left) && isLocationCorrect(myBridge.right) && isLocationEmpty(myLocation) && isLocationEmpty(myLocation))
								{
									bridges.push_back(myBridge);
									myMoving.direction = direction;
									myMoving.locationAfter = myLocation;
									return myMoving;
								}
								continue;
							}
							else
							{
								myMoving.direction = direction;
								myMoving.locationAfter = myLocation;
								return myMoving;
							}
						}

					}
				}

				if (myMoving.locationAfter.get_x() == -1 || myMoving.locationAfter.get_y()  == -1)
				{
					random_device random;
					mt19937 gen(random());
					uniform_int_distribution<> distr(0, boardSize - 1);
					Location rand_location;
					rand_location.set_x(gen());
					rand_location.set_y(gen());
				}
				return myMoving;
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
				
			

			Bridge::Bridge()
			{
				Location _left, _right;
				Bridge bridge(_left,_right);
			}

			Bridge::Bridge(Location _left, Location _right)
			{
				left = _left;
				right = _right;
			}

			void Bridge::set(Location _left, Location _right)
			{
				left = _left;
				right = _right;
			}



			const Bridge Bridge::get()
			{
				const Bridge newBridge(left, right);
				return newBridge;
			}

			bool Hex::isGameEnded()
			{
				vector<Location> ScannedLocations;
				Location myLocation;
				if (playerTurn == 1)
					myLocation = lastLocationOfUser1;
				else
					myLocation = lastLocationOfUser2;

				if (isPathCompleted(myLocation, ScannedLocations))				// if the path is completed then sets the winner.
				{
					isFinished = true;
					winner = playerTurn == 1 ? user1 : user2;
					return true;
				}
				return false;
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

			istream& operator>>(istream& in, std::list<Bridge> bridges)
			{
				short reading;
				in >> reading;
				while (reading != ';')
				{												// bu döngüyle bridge' leri dosyadan tek tek çeker.
					Bridge myBridge;
					myBridge.left.set_x(reading);
					int a, b, c;
					in >> a >> b >> c;

					myBridge.left.set_y(a);
					myBridge.right.set_x(b);
					myBridge.right.set_y(c);

					bridges.push_back(myBridge);
					in >> reading;
				}
				return in;
			}

			Hex::Cell::Cell(int x, int y, CellState state)
				{
					location.setLocation(x, y);
					cellState = state;
				}
			
