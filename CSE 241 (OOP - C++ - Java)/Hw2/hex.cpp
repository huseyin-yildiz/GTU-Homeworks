#include<iostream>
#include<list>
#include<string>
#include<random> 
#include<fstream>
#include"hex.h"
#include"hexPlayer.h"

using namespace std;


			void createMatrix(game & myGame)										// creates matrix of the game
			{
				for (int i = 0; i < MAX_BOARD_SIZE ; ++i)
				{
					for (int j = 0; j < MAX_BOARD_SIZE; ++j)
					{
						if(i < myGame.boardSize && j < myGame.boardSize)
							myGame.matrix[i][j] = cellState::dot;
						else
							myGame.matrix[i][j] = cellState::nope;							
					}
				}   
			}

			void clearScreen(){														// clears the screen
				cout << "\033[2J\033[1;1H";
			}

			void display(const game & myGame)										// displays the last situation of the board				
			{
				clearScreen();
				cout << "  ";
				for (int letter = 0; letter < myGame.boardSize; letter++)
					cout << char('a' + letter) <<' ';
				cout << endl;
				for(int i = 0; i<myGame.boardSize; i++)
				{
					cout << i+1<<' ';
					for(int space=0; space< (i>8?i-1:i); space++)
						cout<<" ";
						
					for(int j=0; j<myGame.boardSize; j++ )
					{
						cout<<myGame.matrix[i][j]<<" ";
					}
					cout<<"\n";
				}
			}


			void play(game & myGame,location myLocation)							// plays given location to the board
			{

				if(myGame.playerTurn == 1)
					{
						myGame.matrix[myLocation.x][myLocation.y] = cellState::user1;			
						myGame.lastLocationOfUser1 = myLocation;
					}
				else if(myGame.playerTurn == 2)
					{
						myGame.matrix[myLocation.x][myLocation.y] = cellState::user2;											// bilgisayar implementasyonu eksik
						
					}
			}

			bool isLocationCorrect(const location myLocation,const int boardSize)												// check if given location is correct (if its on the matrix or not)
			{
				if(myLocation.x > boardSize || myLocation.y > boardSize || myLocation.x < 0 || myLocation.y < 0)
					return false;
				return true;
			}			

			bool isLocationEmpty(const location myLocation,const game & myGame){												// checks the given location if its empty
				if(myGame.matrix[myLocation.x][myLocation.y] == cellState::dot)
					return true;
				return false;				
				}

			location takeLocation(game & myGame)																				// takes a Location or SAVE-LOAD command from the user
			{
				
				try{

					string PlayerNow = myGame.user2;
					if( myGame.playerTurn == 1 )
						PlayerNow = myGame.user1;

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
									return takeLocation(myGame);
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for loading !!\n";
											return takeLocation(myGame);
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);
									loadSavedGame(stringLocation,myGame) ;
									return takeLocation(myGame);
								}
						}
					if( stringLocation.substr(0,4) == "SAVE" )										// if user enters SAVE command, then it saves the game
						{
							if(stringLocation[4] != ' ' )
								{
									cerr << "Please put a white space after the SAVE command !!\n";
									return takeLocation(myGame);
								}
							else{
									if(stringLocation.length() <= 5)
										{
											cerr << "Please enter a name for saving !!\n";
											return takeLocation(myGame);
										}
									stringLocation = stringLocation.substr(5,stringLocation.size()-1);	
									saveGame(myGame,stringLocation) ;
									return takeLocation(myGame);
								}
						}
					if(!isdigit(stringLocation[1]) )
						throw 20;

					location myLocation;
					myLocation.x = stoi(stringLocation.substr(1,stringLocation.size()-1)) -1;
					myLocation.y = stringLocation[0] - 'A';

					if( ! isLocationCorrect(myLocation,myGame.boardSize))
						throw 20;

					return myLocation;
						
					}

				catch(int e){
					cerr << "\nYou entered wrong number !!!\n";
					return takeLocation(myGame);
				}

			}
				

            game menu()																			// shows the main menu and takes preferences
			{
                game myGame;
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
				cin>>myGame.user1;
				clearScreen();
				if(selection1 == '2')
				{
					cout<<"Name for User 2\n";
					cin>>myGame.user2;
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
					myGame.boardSize = selection+5;
				else
					{
						cerr<<"\nYou entered wrong number";
						goto boardSize;
					}
				
                createMatrix(myGame);
                return myGame;
			}

			bool isOnOwnBorder(location myLocation, game & myGame){							// aldığı konumun kendi sınırlarında olup olmadığını bulur.
				if(myGame.matrix[myLocation.x][myLocation.y] == cellState::user1)
					if(myLocation.x == 0 || myLocation.x == myGame.boardSize-1)
						return true;
				if(myGame.matrix[myLocation.x][myLocation.y] == cellState::user2)
					if(myLocation.y == 0 || myLocation.y == myGame.boardSize-1)
						return true;
				return false;
			}

			bool isUserLocationOwner(location myLocation,game & myGame){
				short owner = 0;																								// sıfır ise sahipsiz
				char locationValue = owner = myGame.matrix[myLocation.x][myLocation.y];
				if(locationValue == cellState::user1)
					owner = 1;
				else if(locationValue == cellState::user2)
					owner = 2;
				
				return owner == myGame.playerTurn ? true : false; 
				
			}

			bool isInScanned(const location myLocation,const location scannedLocations[] ){
				int i = 0;
				while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default location değerine eşit olmayınca arar
					{
						if ( scannedLocations[i].x == myLocation.x && scannedLocations[i].y == myLocation.y)
						return true;
						i++;
					}
				return false;	
			}

			void addToScannedLocations(location newLocation,location* scannedLocations,int* locationSize){
				for (int i = 0; i < *locationSize; i++)
					if( scannedLocations[i].x == -1 && scannedLocations[i].y == -1)	// default olarak ayarlanan değere eşit ise
						{
							scannedLocations[i] = newLocation;
							break;
						}
			}

			bool isBordersConnected(location* scannedLocations, short user,short bordSize){			
				bool isBorder1Connected=false, isBorder2Connected = false;
				int i = 0;

				if(user == 2)
					while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default location değerine eşit olmayınca arar
					{
						if(scannedLocations[i].x == 0)
							isBorder1Connected = true;
						else if( scannedLocations[i].x == bordSize-1  )
							isBorder2Connected = true;
						i++;
					}

				else if(user == 1)
					while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default location değerine eşit olmayınca arar
					{
						if(scannedLocations[i].y == 0)
							isBorder1Connected = true;
						else if( scannedLocations[i].y == bordSize-1  )
							isBorder2Connected = true;
						i++;
					}
				
				return isBorder1Connected && isBorder2Connected ? true : false;															
				
			}

			location setLocation(location myLocation, int x , int y){									// sets the given location 
				decltype(myLocation) newLocation;
				newLocation.x = myLocation.x + x;
				newLocation.y = myLocation.y + y;
				return newLocation;
			}

			

			

			bool isPathCompleted (location myLocation,game & myGame, location scannedLocations[]){			// checks if Path is completed or not
				int locationSize = myGame.boardSize * myGame.boardSize /2;
				
				list<location> connections = findConnections(myLocation,myGame.boardSize);
		//		list<location>::iterator it;																			
				for( auto it = connections.begin(); it != connections.end(); it++)
				{	
					if(isLocationCorrect(*it,myGame.boardSize) && isUserLocationOwner(*it,myGame) )
					{
						if( isInScanned(*it, scannedLocations) )
							continue;
						else
							{
								addToScannedLocations(*it,scannedLocations,&locationSize);
								isPathCompleted(*it,myGame,scannedLocations);
							}
					}
				}
				if( isBordersConnected(scannedLocations, myGame.playerTurn,myGame.boardSize) )
							{
								int a = 0;
								while(scannedLocations[a].x != -1){
									myGame.matrix[scannedLocations[a].x][scannedLocations[a].y] = myGame.playerTurn == 2 ? 'X' : 'O';
									a++;
								}
								return true;
							}
				return false ;
			}
				

			void changePlayer(game & myGame){									// changes the player now
				if( myGame.playerTurn == 1 )
					myGame.playerTurn = 2;
				else
					myGame.playerTurn = 1;
			}

			void showResults(game & myGame){							// shows which user is winner
				
				display(myGame);
				cout << "\n\n !!!!!  " << myGame.winner << "  is winner, Congratulations  !!!!!\n";

			}
			

			bool loadSavedGame(string fileName,game & myGame)					// loads the saved game
			{
				ifstream inputStream(fileName.c_str());
				if(inputStream.fail())
				{
					display(myGame);
					cerr << endl << fileName << " is not found\n";				// if the given file name is not found gives an error to the user.
					return false;
				}
				else
				{
					inputStream >> myGame.boardSize								// if file name is found then start to copy the values row by row.
					>> myGame.user1 >> myGame.user2 ;							// each row is for one variable or array
					inputStream.get();
					for (int i = 0; i < MAX_BOARD_SIZE; i++)									// matrix kaydedilir
					{
						for (int j = 0; j < MAX_BOARD_SIZE; j++)
							myGame.matrix[i][j] = inputStream.get();
					}
					inputStream.get();
					
					inputStream >> myGame.isFinished		
					>> myGame.playerTurn
					>> myGame.lastLocationOfUser1.x >> myGame.lastLocationOfUser1.y
					>> myGame.lastLocationOfUser2.x >> myGame.lastLocationOfUser2.y 
					>> myGame.firstLocationOfUser1.x >> myGame.firstLocationOfUser1.y
					>> myGame.firstLocationOfUser2.x >> myGame.firstLocationOfUser2.y ; 
					
					short reading ;
					inputStream >> reading;
					while( reading != ';' )	
					{												// bu döngüyle bridge' leri dosyadan tek tek çeker.
						bridge myBridge;
						myBridge.left.x = reading;
						inputStream >> myBridge.left.y;
						inputStream >> myBridge.right.x ;
						inputStream >> myBridge.right.y ;
						
						myGame.bridges.push_back(myBridge);
						inputStream >> reading;
					}

					short mvm1,mvm2;
					inputStream >> mvm1 >> mvm2 ;
					myGame.lastMovementOfUser1 = (movement)mvm1;
					myGame.lastMovementOfUser2 = (movement)mvm2;

					inputStream.close();
					display(myGame);
					cout << "\nThe file loaded successfully\n";							// if the loading is successcfull then gives an output to the user.
					return true;

				}
			
			}


			bool saveGame(game & myGame, string fileName)								// To save the game and all variables and arrays etc.
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

					outputStream << myGame.boardSize << endl
					<< myGame.user1 << ' ' << myGame.user2 << endl;
					
					for (int i = 0; i < MAX_BOARD_SIZE; i++)									// saves the matrix array 
					{
						for (int j = 0; j < MAX_BOARD_SIZE; j++)
							outputStream << myGame.matrix[i][j];	
					}

					outputStream << endl << myGame.isFinished << endl		
					<< myGame.playerTurn << endl
					<< myGame.lastLocationOfUser1.x << ' ' << myGame.lastLocationOfUser1.y << ' '
					<< myGame.lastLocationOfUser2.x << ' ' << myGame.firstLocationOfUser2.y << ' '
					<< myGame.firstLocationOfUser1.x <<' '<< myGame.firstLocationOfUser1.y << ' '
					<< myGame.firstLocationOfUser2.x <<' '<< myGame.firstLocationOfUser2.y << ' ' << endl; 
					
					for(auto bridgeTosave : myGame.bridges)										// saves the bridges
					{
						outputStream << bridgeTosave.left.x <<' '<< bridgeTosave.left.y << ' '
						<< bridgeTosave.right.x << ' ' << bridgeTosave.right.y << ' ';
					}

					outputStream << int(';') << endl << myGame.lastMovementOfUser1 << ' ' << myGame.lastMovementOfUser2 ;

					outputStream.close();
					cout << "The game saved successfully\n";
					return true;	
				}

			}


