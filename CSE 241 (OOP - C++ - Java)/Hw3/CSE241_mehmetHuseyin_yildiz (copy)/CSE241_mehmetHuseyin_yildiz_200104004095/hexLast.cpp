#include<iostream>
#include"hex.h"


using namespace std;

bool Hex::newGame{ false };
int Hex::gameNow{ 0 };
int Hex::compare1{ -1 };
int Hex::compare2{ -1 };

int main() {

//	cout << "\e[8;50;100t";

	vector<Hex> hexGames;
	Hex firstGame;
	firstGame.menu();
	hexGames.push_back(firstGame);


	while (hexGames.size() != 0)
	{
		if (Hex::gameNow > hexGames.size())
		{
			cerr << "There is no game with this number. ";
			Hex::gameNow = 0;
		}

		hexGames[Hex::gameNow].PlayGame();
		hexGames[0].clearScreen();
		cout << "Games at now:\n";
		for (int i = 0; i < hexGames.size(); i++)
			cout << i << ")" << hexGames[i].user1 << "-" << hexGames[i].user2 << endl ;
		cout << "Examples to play:\n1)SAVE FILENAME\n2)LOAD FILENAME\n3)NEW\n4)COMPARE 1 2\n5)GAME 1\n6)f5" << endl << endl << endl;
		if (Hex::newGame == true)
		{

			Hex newGame;
			newGame.menu();
			hexGames.push_back(newGame);
			Hex::newGame = false;
			Hex::gameNow = hexGames.size() - 1;
		}

		if (Hex::compare1 != -1)
		{
			if (hexGames[Hex::compare1].isMarkedCellsMore(hexGames[Hex::compare2]))
				cout << Hex::compare1 << " has more marked cells than " << Hex::compare2 <<endl;
			else
				cout << Hex::compare2 << " has more marked cells than " << Hex::compare1 << endl;
		}
		if(hexGames[Hex::gameNow].isFinished)
		{
			hexGames[Hex::gameNow].showResults();
		}
	}
	

		return 0;
}
































































/////////////////////////////











	

/*

	Hex::Hex(){
		 menu();
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
				cout<<"Select board size Please\n"<<"1) 6x6\n2)7x7\n3)8x8\n4)9x9\n5)10x10\n6)11x11\n7)12x12\n";			// takes board size
				string a;
				getline(cin,a);
				selection = stoi(a);
				clearScreen();
				if( selection < 8 && selection > 0 )
					boardSize = selection+5;
				else
					{
						cerr<<"\nYou entered wrong number";
						goto boardSize;
					}
				
                createMatrix();

			}
	
		void Hex::display()										// displays the last situation of the board				
			{
				clearScreen();
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
						cout<<matrix[i][j]<<" ";
					}
					cout<<"\n";
				}
			}
			
	void Hex::clearScreen()
	{														// clears the screen
				cout << "\033[2J\033[1;1H";
	}
	
	
	
			void Hex::play(Location myLocation)							// plays given Location to the board
			{

				if(playerTurn == 1)
					{
						matrix[myLocation.x][myLocation.y] = CellState::user1;			
						lastLocationOfUser1 = myLocation;
					}
				else if(playerTurn == 2)
					{
						matrix[myLocation.x][myLocation.y] = CellState::user2;											// bilgisayar implementasyonu eksik
						
					}
			}			

			Location Location::changeLocation(int x_,int y_)
			{
				Location newLocation;
				newLocation.x = x+x_;
				newLocation.y = y+y_;
				return newLocation;
			}
	
			bool Hex::isLocationCorrect(const Location myLocation)												// check if given Location is correct (if its on the matrix or not)
			{
				if(myLocation.x > boardSize || myLocation.y > boardSize || myLocation.x < 0 || myLocation.y < 0)
					return false;
				return true;
			}			
			
           
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

					cout << PlayerNow << " please make a move: ";
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
					if(!isdigit(stringLocation[1]) )
						throw 20;

					Location myLocation;
					myLocation.x = stoi(stringLocation.substr(1,stringLocation.size()-1)) -1;
					myLocation.y = stringLocation[0] - 'A';

					if( ! isLocationCorrect(myLocation))
						throw 20;

					return myLocation;
						
					}

				catch(int e){
					cerr << "\nYou entered wrong number !!!\n";
					return takeLocation();
				}

			}
			
				bool Hex::isInScanned(const Location myLocation,const Location scannedLocations[] ){
				int i = 0;
				while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default Location değerine eşit olmayınca arar
					{
						if ( scannedLocations[i].x == myLocation.x && scannedLocations[i].y == myLocation.y)
						return true;
						i++;
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
			
			
			bool Hex::isBordersConnected(Location* scannedLocations)
			{			
				bool isBorder1Connected=false, isBorder2Connected = false;
				int i = 0;

				if(playerTurn == 2)
					while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default Location değerine eşit olmayınca arar
					{
						if(scannedLocations[i].x == 0)
							isBorder1Connected = true;
						else if( scannedLocations[i].x == boardSize-1  )
							isBorder2Connected = true;
						i++;
					}

				else if(playerTurn == 1)
					while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default Location değerine eşit olmayınca arar
					{
						if(scannedLocations[i].y == 0)
							isBorder1Connected = true;
						else if( scannedLocations[i].y == boardSize-1  )
							isBorder2Connected = true;
						i++;
					}
				
				return isBorder1Connected && isBorder2Connected ? true : false;															
				
			}

			
			
			
			bool Hex::isPathCompleted (Location myLocation, Location scannedLocations[])			// checks if Path is completed or not
			{
				int locationSize = boardSize * boardSize /2;
				
				list<Location> connections = findConnections(myLocation);
		//		list<location>::iterator it;																			
				for( auto it = connections.begin(); it != connections.end(); it++)
				{	
					if(isLocationCorrect(*it) && isUserLocationOwner(*it) )
					{
						if( isInScanned(*it, scannedLocations) )
							continue;
						else
							{
								addToScannedLocations(*it,scannedLocations,&locationSize);
								isPathCompleted(*it,scannedLocations);
							}
					}
				}
				if( isBordersConnected(scannedLocations ) )
							{
								int a = 0;
								while(scannedLocations[a].x != -1){
									matrix[scannedLocations[a].x][scannedLocations[a].y] = playerTurn == 2 ? 'X' : 'O';
									a++;
								}
								return true;
							}
				return false ;
			}
			
			
			
			
			
			
				bool Hex::isOnOwnBorder(Location myLocation){							// aldığı konumun kendi sınırlarında olup olmadığını bulur.
				if(matrix[myLocation.x][myLocation.y] == CellState::user1)
					if(myLocation.x == 0 || myLocation.x == boardSize-1)
						return true;
				if(matrix[myLocation.x][myLocation.y] == CellState::user2)
					if(myLocation.y == 0 || myLocation.y == boardSize-1)
						return true;
				return false;
			}

			bool Hex::isUserLocationOwner(Location myLocation){
				short owner = 0;																								// sıfır ise sahipsiz
				char locationValue = owner = matrix[myLocation.x][myLocation.y];
				if(locationValue == CellState::user1)
					owner = 1;
				else if(locationValue == CellState::user2)
					owner = 2;
				
				return owner == playerTurn ? true : false; 
				
			}



			void Hex::addToScannedLocations(Location newLocation,Location* scannedLocations,int* locationSize){
				for (int i = 0; i < *locationSize; i++)
					if( scannedLocations[i].x == -1 && scannedLocations[i].y == -1)	// default olarak ayarlanan değere eşit ise
						{
							scannedLocations[i] = newLocation;
							break;
						}
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
					for (int i = 0; i < MAX_BOARD_SIZE; i++)									// matrix kaydedilir
					{
						for (int j = 0; j < MAX_BOARD_SIZE; j++)
							matrix[i][j] = inputStream.get();
					}
					inputStream.get();
					
					inputStream >> isFinished		
					>> playerTurn
					>> lastLocationOfUser1.x >> lastLocationOfUser1.y
					>> lastLocationOfUser2.x >> lastLocationOfUser2.y 
					>> firstLocationOfUser1.x >> firstLocationOfUser1.y
					>> firstLocationOfUser2.x >> firstLocationOfUser2.y ; 
					
					short reading ;
					inputStream >> reading;
					while( reading != ';' )	
					{												// bu döngüyle bridge' leri dosyadan tek tek çeker.
						Bridge myBridge;
						myBridge.left.x = reading;
						inputStream >> myBridge.left.y;
						inputStream >> myBridge.right.x ;
						inputStream >> myBridge.right.y ;
						
						bridges.push_back(myBridge);
						inputStream >> reading;
					}

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
					
					for (int i = 0; i < MAX_BOARD_SIZE; i++)									// saves the matrix array 
					{
						for (int j = 0; j < MAX_BOARD_SIZE; j++)
							outputStream << matrix[i][j];	
					}

					outputStream << endl << isFinished << endl		
					<< playerTurn << endl
					<< lastLocationOfUser1.x << ' ' << lastLocationOfUser1.y << ' '
					<< lastLocationOfUser2.x << ' ' << firstLocationOfUser2.y << ' '
					<< firstLocationOfUser1.x <<' '<< firstLocationOfUser1.y << ' '
					<< firstLocationOfUser2.x <<' '<< firstLocationOfUser2.y << ' ' << endl; 
					
					for(auto bridgeTosave : bridges)										// saves the bridges
					{
						outputStream << bridgeTosave.left.x <<' '<< bridgeTosave.left.y << ' '
						<< bridgeTosave.right.x << ' ' << bridgeTosave.right.y << ' ';
					}

					outputStream << int(';') << endl << lastMovementOfUser1 << ' ' << lastMovementOfUser2 ;

					outputStream.close();
					cout << "The game saved successfully\n";
					return true;	
				}

			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	

	Location Hex::goAhead(Movement myMovement,Location fromThis){							// belirtilen lokasyondan istenilen yönün lokasyonunu döndürür.
				decltype(fromThis) newLocation;
				short mv = myMovement;
				switch(mv){
					case up: newLocation.x = fromThis.x -2; newLocation.y = fromThis.y +1;break;
					case down: newLocation.x = fromThis.x +2; newLocation.y = fromThis.y -1 ;break;
					case rght: newLocation.x = fromThis.x; newLocation.y = fromThis.y +1 ;break;
					case lft: newLocation.x = fromThis.x ; newLocation.y = fromThis.y -1; break;
					case up_left: newLocation.x = fromThis.x -1; newLocation.y = fromThis.y; ;break;
					case up_rght: newLocation.x = fromThis.x -1; newLocation.y = fromThis.y +1 ;break;
					case down_right: newLocation.x = fromThis.x +1; newLocation.y = fromThis.y ;break;
					case down_left: newLocation.x = fromThis.x +1; newLocation.y = fromThis.y -1 ;break;
				}
				return newLocation;
			}

			Location Hex::firstMovement(){												// if this Movement is first Movement selects a locaton.
				random_device random;						
				mt19937 gen(random());
				Location myLocation;
				short middle = boardSize /2;
				uniform_int_distribution<> distr(0,middle-1);

				if (lastLocationOfUser1.y > middle-1 )
					myLocation.y = lastLocationOfUser1.y - distr(gen);
				else
					myLocation.y = distr(gen);
				int difference = lastLocationOfUser1.y - myLocation.y;
				myLocation.x = lastLocationOfUser1.x + (difference < 0 ? -1*difference  : difference)*(2.0/3.0) ;
				if(!isLocationEmpty(myLocation) || myLocation.x == boardSize-1 )
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

			Bridge Hex::findBridge(const Location firsLocation,const Location secondLocation){									// finds a Bridge (points between two point)
				Bridge myBridge;
				if( goAhead(up,firsLocation).x == secondLocation.x && secondLocation.y == (goAhead(up,firsLocation).y))
				{
					myBridge.right.y = secondLocation.y;
					myBridge.right.x = secondLocation.x +1;
					myBridge.left.y = firsLocation.y;
					myBridge.left.x = firsLocation.x -1; 
				}
				if(secondLocation.x == goAhead(down,firsLocation).x && goAhead(down,firsLocation).y == secondLocation.y)
				{
					myBridge.right.y = firsLocation.y;
					myBridge.right.x = firsLocation.x +1;
					myBridge.left.y = secondLocation.y;
					myBridge.left.x = secondLocation.x -1; 
				}
				if(secondLocation.x == goAhead(up_2nd_right,firsLocation).x && goAhead(up_2nd_right,firsLocation).y == secondLocation.y)
				{
					myBridge.right.y = firsLocation.y +1;
					myBridge.right.x = firsLocation.x;
					myBridge.left.y = firsLocation.y +1;
					myBridge.left.x = secondLocation.x; 
				}
				if(secondLocation.x == goAhead(up_2nd_left,firsLocation).x && goAhead(up_2nd_left,firsLocation).y == secondLocation.y)
				{
					myBridge.right.y = firsLocation.y;
					myBridge.right.x = secondLocation.x;
					myBridge.left.y = secondLocation.y;
					myBridge.left.x = firsLocation.y; 
				}
				if(secondLocation.x == goAhead(down_2nd_right,firsLocation).x && goAhead(down_2nd_right,firsLocation).y == secondLocation.y)
				{
					myBridge.right.y = secondLocation.y;
					myBridge.right.x = firsLocation.x;
					myBridge.left.y = firsLocation.y;
					myBridge.left.x = secondLocation.x; 
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

				if(bridges.size() > 0)
				for(auto it = bridges.begin(); it != bridges.end(); it++ )				// Bridge lerden biri dolunursa diğerini alır.
					{
						if(matrix[(*it).left.x][(*it).left.y] == CellState::user1 )
							{
								myLocation.x = (*it).right.x;
								myLocation.y = (*it).right.y;
								myMoving.locationAfter = myLocation;
								myMoving.isItBridging = true;
								bridges.erase(it);

								return myMoving;
							}
						if(matrix[(*it).right.x][(*it).right.y] == CellState::user1){
							myLocation.x = (*it).left.x;
							myLocation.y = (*it).left.y;
							myMoving.locationAfter = myLocation;
							myMoving.isItBridging = true;
								bridges.erase(it);

								return myMoving;
						}
					}

					if( (lastLocationOfUser2.x >= boardSize -2 && firstLocationOfUser2.x <= 1) || (lastLocationOfUser2.x <=1 && firstLocationOfUser2.x >= boardSize -2) )		// iki tarafta border a yetişirse Bridge leri doldur
					{	for( auto it = bridges.begin(); it != bridges.end(); it++){
							if( isLocationEmpty( Bridge(*it).left ))
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
				if(lastLocationOfUser2.x == boardSize -2 && lastMovementOfUser2 != up )	// alt border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.
				{

					if(myLocation.y == 0)
					{
						myMoving.direction = down_right;
						myMoving.locationAfter.x = boardSize -1;	
						myMoving.locationAfter.y = 0;
						return myMoving;
					}


					decltype(myLocation) bckp = goAhead(down_left,lastLocationOfUser2);
					myBridge.left = bckp;
					bckp = goAhead(down_right,lastLocationOfUser2);
					myBridge.right = bckp;
					bridges.push_back(myBridge);

					decltype(myLocation) backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = up;								// !!!!!! buraya sonsuz döngüye girmemesi için bi şey koy bi up bi down olacak
					return move();
					}

					if(lastLocationOfUser2.x == boardSize -1 && lastMovementOfUser2 != up){						// alt border'ı tamamladıysa diğerine doğru git
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = up;
					return move();
					}

				if(lastLocationOfUser2.x == 1 && lastMovementOfUser2 != down){					// üst border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.

					if(myLocation.y == boardSize-1)
					{
						myMoving.direction = up_left;
						myMoving.locationAfter.x = 0;
						myMoving.locationAfter.y = boardSize -1;
						return myMoving;
					}


					myBridge.left.x = 0;
					myBridge.left.y = lastLocationOfUser2.y;
					myBridge.right.x = 0;
					myBridge.right.y = lastLocationOfUser2.y +1;
					bridges.push_back(myBridge);
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = down;
					return move();
				}

				if(lastLocationOfUser2.x == 0 && lastMovementOfUser2 != up){						// üst border ı tamamladıysa diğerine doğru git
					Location backup = firstLocationOfUser2;
					firstLocationOfUser2 = lastLocationOfUser2;
					lastLocationOfUser2 = backup;
					lastMovementOfUser2 = down;
					return move();
				}

				if(lastMovementOfUser2 == no){									// yön belirleme için
					if(lastLocationOfUser1.x <= lastLocationOfUser2.x)				// son hamle rakibin hamlesinin üstünde ise
					{
						Movement mvmnts[]={up,up_2nd_right,up_2nd_left} ;
						for(auto m : mvmnts){											// burası da
							myLocation = goAhead(m,lastLocationOfUser2);						
							myBridge = findBridge(myLocation,lastLocationOfUser2);
							if(!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = lastLocationOfUser2.x > firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								else if(!isLocationEmpty(myBridge.right), !isUserLocationOwner(myBridge.left) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = lastLocationOfUser2.x > firstLocationOfUser2.x ? down : up; 
										return myMoving;
									}

								else if(isLocationEmpty(myLocation) && myBridge.left.x != -1 && myBridge.right.x != -1 )
								{
									myMoving.direction = m;
									break;	
								}
						}
						myMoving.locationAfter = myLocation;
					}
					else 
					{
						Movement mvmnts[]={down,down_2nd_right,down_2nd_left} ;
							for(auto m : mvmnts){									
								myLocation = goAhead(m,lastLocationOfUser2);						
								myBridge = findBridge(myLocation,lastLocationOfUser2);
								if(isLocationEmpty(myLocation) && myBridge.left.x != -1 && myBridge.right.x != -1 )
								{
									myMoving.direction = m;
									break;			
								}				
							}
							myMoving.locationAfter = myLocation;
					}
					bridges.push_back( myBridge);			// Bridge kontrolu yap !!
					return myMoving; 
				}
				
				else																							// yön belirli ise
				{	
				//	short range = 0;						// !! yukarı ise
					list<Movement> upDirections = {up,up_2nd_left,up_2nd_right,up_left,up_rght,lft,rght};					// yön sıralaması
					list<Movement> downDirections= {down,down_2nd_right,down_2nd_left,down_right,down_left,rght,lft};
					list<Movement>directions; 
					if(lastMovementOfUser2 == rght || lastMovementOfUser2 == lft){							// yön sağ veya sol ise yukarı mı aşağı mı gidileceği belirlenir.
						if(lastLocationOfUser2.x > firstLocationOfUser2.x)
							directions = downDirections;
						else
							directions = upDirections;
					}
					else
						{
							if( isContainsDirection(upDirections,lastMovementOfUser2) )
								directions = upDirections;
							else
								directions = downDirections;
						}
					for(auto direction : directions)									
					{
						myLocation = goAhead(Movement(direction),lastLocationOfUser2);
						if(isLocationEmpty(myLocation) && isLocationCorrect(myLocation) ){
							if(direction == up_2nd_right || direction == up_2nd_left || direction == up || direction == down || direction == down_2nd_left || direction == down_2nd_right)
							{
								myBridge = findBridge(lastLocationOfUser2,myLocation);
								if(!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = lastLocationOfUser2.x > firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								if(!isLocationEmpty(myBridge.right) && !isUserLocationOwner(myBridge.right) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left) && !isUserLocationOwner(myBridge.left))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = lastLocationOfUser2.x > firstLocationOfUser2.x ? down : up; 
										return myMoving;
									}
								
								if(isLocationCorrect(myBridge.left) && isLocationCorrect(myBridge.right) && isLocationEmpty(myLocation) && isLocationEmpty(myLocation))
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

				if(myMoving.locationAfter.x == -1 || myMoving.locationAfter.y == -1)
				{	
					random_device random;
					mt19937 gen(random());
					uniform_int_distribution<> distr(0,boardSize-1);
					Location rand_location;
					rand_location.x = gen();
					rand_location.y = gen();
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
				

*/
