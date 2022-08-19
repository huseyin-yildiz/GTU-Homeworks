/*
Hocam verilen ödev pdf inde ne anladıysam onu yaptım. Yatay geçişle bu sene geçiş yaptığım için ödevlerde ne  yapılıp ne yapılmadığı hakkında bir bilgim yok. Eksik bir şey olursa mazur görün lütfen.

g++ hw1_mehmetHuseyinYildiz_200104004095.cpp
./a.out
şeklinde derleyip çalıştırılabiliyor.
*/

#include<iostream>
#include<string>
#include<list>
#include<random> 
//#include<stdlib.h>

using namespace std;

            const short PATHLIMIT = 30;
            const string DEFAULT_NAME = "Computer";
            const short MAX_BOARD_SIZE = 12;
            const short MAX_PATH_SIZE = 30;
			const short MAX_CHILD_SIZE = 30;
			const short DEEPNESS = 3;

			struct location
			{
				int x=-1;
				int y=-1;
			};

			struct  bridge
			{
				location left,right;
			};
			

			enum movement{no,up,down,rght,lft,up_rght,up_left,down_right,down_left,up_2nd_right,up_2nd_left,down_2nd_right,down_2nd_left};		

			struct moving
			{
				movement direction;
				location locationBefore, locationAfter;
				bool isItBridging=false;
			};
			

            struct game			// oyunun genel yapısı için
            {
                int boardSize;
                string user1, user2 = DEFAULT_NAME,winner = "";
                char matrix [MAX_BOARD_SIZE] [MAX_BOARD_SIZE] = {{' '}};
    			bool isFinished = false;
		    	short playerTurn=1;
				location lastLocationOfUser1,lastLocationOfUser2,firstLocationOfUser1,firstLocationOfUser2;
				list<bridge> bridges;
				movement lastMovementOfUser1 = no,lastMovementOfUser2 = no;
            };

			void createMatrix(game* myGame)
			{
				for (int i = 0; i < myGame->boardSize ; ++i)
				{
					for (int j = 0; j < myGame->boardSize; ++j)
					{
						myGame->matrix[i][j] = '.';
					}
				}   
			}

			void clearScreen(){			// ekranı temixler
				cout << "\033[2J\033[1;1H";
			}

			void display(game* myGame)		//	oyun matrixini gösterir
			{
				clearScreen();
				cout << "  ";
				for (int letter = 0; letter < myGame->boardSize; letter++)
					cout << char('a' + letter) <<' ';
				cout << endl;
				for(int i = 0; i<myGame->boardSize; i++)
				{
					cout << i+1<<' ';
					for(int space=0; space< (i>8?i-1:i); space++)
						cout<<" ";
						
					for(int j=0; j<myGame->boardSize; j++ )
					{
						cout<<myGame->matrix[i][j]<<" ";
					}
					cout<<"\n";
				}
			}


			void play(game* myGame,location myLocation)			// verilen konuma matrixte yerleştirmr yapar.
			{

				if(myGame->playerTurn == 1)
					{
						myGame->matrix[myLocation.x][myLocation.y] = 'o';			
						myGame->lastLocationOfUser1 = myLocation;
					}
				else if(myGame->playerTurn == 2)
					{
						myGame->matrix[myLocation.x][myLocation.y] = 'x';											// bilgisayar implementasyonu eksik
						
					}
			}

			bool isLocationCorrect(location myLocation,int boardSize)												// verilen konumun matrix sınırları içinde olup oladığını kontrol eder.
			{
				if(myLocation.x > boardSize || myLocation.y > boardSize || myLocation.x < 0 || myLocation.y < 0)
					return false;
				return true;
			}			

			bool isLocationEmpty(location myLocation,game* myGame){								// verilen konumun boş olup olmadığını kontrol eder.
				if(myGame->matrix[myLocation.x][myLocation.y] == '.')
					return true;
				return false;
				
				}


			location takeLocation(game* myGame)							// user dan konum alır
			{
				
				try{

					string PlayerNow = myGame->user2;
					if( myGame->playerTurn == 1 )
						PlayerNow = myGame->user1;

					string stringLocation;

					cout << PlayerNow << " please make a move: ";
					cin>>stringLocation;
					stringLocation[0] = toupper(stringLocation[0]);
					if(!isdigit(stringLocation[1]) )
						throw 20;

					location myLocation;
					myLocation.x = stoi(stringLocation.substr(1,stringLocation.size()-1)) -1;
					myLocation.y = stringLocation[0] - 'A';

					if( ! isLocationCorrect(myLocation,myGame->boardSize))
						throw 20;

					return myLocation;
						
					}

				catch(int e){
					cerr << "\nYou entered wrong number !!!\n";
					return takeLocation(myGame);
				}

			}
				

            game menu()					// oyunun giriş menuleri gosterir
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
				cin>>selection1;
				if(selection1 !='1'  &&  selection1 != '2' )
					anyError = true;
				clearScreen();
				}
				while(anyError);


				cout<<"Name for User 1\n";
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
				cout<<"Select board size Please\n"<<"1) 6x6\n2)7x7\n3)8x8\n4)9x9\n5)10x10\n6)11x11\n7)12x12\n";
				cin>>selection;
				clearScreen();
				if( selection < 8 && selection > 0 )
					myGame.boardSize = selection+5;
				else
					{
						cerr<<"\nYou entered wrong number";
						goto boardSize;
					}
				
                createMatrix(&myGame);
                return myGame;
			}

			bool isOnOwnBorder(location myLocation, game* myGame){					// aldığı konumun kendi sınırlarında olup olmadığını bulur.
				if(myGame->matrix[myLocation.x][myLocation.y] == 'o')
					if(myLocation.x == 0 || myLocation.x == myGame->boardSize-1)
						return true;
				if(myGame->matrix[myLocation.x][myLocation.y] == 'x')
					if(myLocation.y == 0 || myLocation.y == myGame->boardSize-1)
						return true;
				return false;
			}

			bool isUserLocationOwner(location myLocation,game* myGame){					// verilen konumun o anki kullanıcı olup olmadığını belirler
				short owner = 0;																								// sıfır ise sahipsiz
				char locationValue = owner = myGame->matrix[myLocation.x][myLocation.y];
				if(locationValue == 'o')
					owner = 1;
				else if(locationValue == 'x')
					owner = 2;
				
				return owner == myGame->playerTurn ? true : false; 
				
			}

			bool isInScanned(location myLocation, location scannedLocations[] ){			// verilen konumun dizi içinde olup olmadığını belirler
				int i = 0;
				while(scannedLocations[i].x != -1 && scannedLocations[i].x != -1)												//default location değerine eşit olmayınca arar
					{
						if ( scannedLocations[i].x == myLocation.x && scannedLocations[i].y == myLocation.y)
						return true;
						i++;
					}
				return false;	
			}

			void addToScannedLocations(location newLocation,location* scannedLocations,int* locationSize){			// taranan konumlara ekler
				for (int i = 0; i < *locationSize; i++)
					if( scannedLocations[i].x == -1 && scannedLocations[i].y == -1)	// default olarak ayarlanan değere eşit ise
						{
							scannedLocations[i] = newLocation;
							break;
						}
			}

			bool isBordersConnected(location* scannedLocations, short user,short bordSize){						// karşılıklı kenarların bağlı olup olmadığını kontrol eder
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

			location setLocation(location myLocation, int x, int y){			//	belli bir konumu düzenlemek için 
				location newLocation;
				newLocation.x = myLocation.x + x;
				newLocation.y = myLocation.y + y;
				return newLocation;
			}

			list<location> findConnections(location myLocation,short boardSize){		// bir konumun komşularını bulur ve döndürür
				list <location> connections;
				connections.push_back(myLocation);
				connections.push_back( setLocation(myLocation,-1,0) ); 
				connections.push_back( setLocation(myLocation,1,0) );	
				connections.push_back( setLocation(myLocation,0,-1) ); 
				connections.push_back( setLocation(myLocation,0,1) ); 
				connections.push_back( setLocation(myLocation,-1,1) );
				connections.push_back( setLocation(myLocation,1,-1) );

				list<location>::iterator it;
				for(it=connections.begin(); it != connections.end();it++)
					if( !isLocationCorrect(*it,boardSize) )
							connections.erase(it--);
						
				return connections;
			}

			

			bool isPathCompleted (location myLocation,game* myGame, location scannedLocations[]){			// path in oluşturulup oluşmadığını kontrol eder
				int locationSize = myGame->boardSize * myGame->boardSize /2;
				
				list<location> connections = findConnections(myLocation,myGame->boardSize);
				list<location>::iterator it;
				for( it = connections.begin(); it != connections.end(); it++)
				{	
					if(isLocationCorrect(*it,myGame->boardSize) && isUserLocationOwner(*it,myGame) )
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
				if( isBordersConnected(scannedLocations, myGame->playerTurn,myGame->boardSize) )
							{
								int a = 0;
								while(scannedLocations[a].x != -1){
									myGame->matrix[scannedLocations[a].x][scannedLocations[a].y] = myGame->playerTurn == 2 ? 'X' : 'O';
									a++;
								}
								return true;
							}
				return false ;
			}
				

			void changePlayer(game* myGame){				// oyuncu sırası user1 de ise user2 ye 2 de ise 1 geçirir
				if( myGame->playerTurn == 1 )
					myGame->playerTurn = 2;
				else
					myGame->playerTurn = 1;
			}

			void showResults(game* myGame){					// oyun sonucunu gösterir

				display(myGame);
				cout << "\n\n !!!!!  " << myGame->winner << "  is winner, Congratulations  !!!!!\n";

			}
			
			// Computer Playings Things


			location goAhead(movement myMovement,location fromThis){							// belirtilen lokasyondan istenilen yönün lokasyonunu döndürür.
				location newLocation;
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

			location firstMovement(game* myGame){												// computer için ilk konumu belirler
				random_device random;
				mt19937 gen(random());
				location myLocation;
				short middle = myGame->boardSize/2;
				uniform_int_distribution<> distr(0,middle-1);

				if (myGame ->lastLocationOfUser1.y > middle-1 )
					myLocation.y = myGame->lastLocationOfUser1.y - distr(gen);
				else
					myLocation.y = distr(gen);
				int difference = myGame->lastLocationOfUser1.y - myLocation.y;
				myLocation.x = myGame->lastLocationOfUser1.x + (difference < 0 ? -1*difference  : difference)*(2.0/3.0) ;
				if(!isLocationEmpty(myLocation,myGame) || myLocation.x == myGame->boardSize-1 )
					return firstMovement(myGame);
				myGame->firstLocationOfUser2 = myLocation;
				return myLocation;
			}

			bool isContainsDirection(list<movement> directions, movement direction)			// belirli bir yönün yön listesi içinde olup olmadığını belirler
			{
				for(movement m : directions)
				{
					if(direction == m)
					return true;
				}
				return false;
			}

			bridge findBridge(location firsLocation,location secondLocation){						// iki konum arası varsa 2 ara bağlantıyı bulur
				bridge myBridge;
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

			moving move(game* myGame){															// computer için hamle yapar
				location myLocation;
				bridge myBridge;
				moving myMoving;
				list<bridge>::iterator it;
				myMoving.locationBefore = myGame->lastLocationOfUser2;

				if(myGame->bridges.size() > 0)
				for(it=myGame->bridges.begin(); it != myGame->bridges.end(); it++ )				// bridge lerden biri dolunursa diğerini alır.
					{
						if(myGame->matrix[(*it).left.x][(*it).left.y] == 'o' )
							{
								myLocation.x = (*it).right.x;
								myLocation.y = (*it).right.y;
								myMoving.locationAfter = myLocation;
								myMoving.isItBridging = true;
								myGame->bridges.erase(it);
						//		if(isLocationsConnected(myMoving.locationBefore,myMoving.locationAfter) &&)

								return myMoving;
							}
						if(myGame->matrix[(*it).right.x][(*it).right.y] == 'o'){
							myLocation.x = (*it).left.x;
							myLocation.y = (*it).left.y;
							myMoving.locationAfter = myLocation;
							myMoving.isItBridging = true;
								myGame->bridges.erase(it);

								return myMoving;
						}
					}

					if( (myGame->lastLocationOfUser2.x >= myGame->boardSize -2 && myGame->firstLocationOfUser2.x <= 1) || (myGame->lastLocationOfUser2.x <=1 && myGame->firstLocationOfUser2.x >= myGame->boardSize -2) )		// iki tarafta border a yetişirse bridge leri doldur
					{list<bridge>::iterator it;
						for( it = myGame->bridges.begin(); it != myGame->bridges.end(); it++){
							if( isLocationEmpty( bridge(*it).left,myGame ))
								{
									bridge dlt = *it;
									myGame->bridges.erase(it);
									myMoving.isItBridging = true;
									myMoving.locationAfter = dlt.left;
									return myMoving;
								}
							else
							{
								bridge dlt = *it;
								myGame->bridges.erase(it);
								myMoving.isItBridging = true;
								myMoving.locationAfter = dlt.right;
								return myMoving;
							}
							
						}		
					}
				if(myGame->lastLocationOfUser2.x == myGame->boardSize -2 && myGame->lastMovementOfUser2 != up )	// alt border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.
				{

					if(myLocation.y == 0)
					{
						myMoving.direction = down_right;
						myMoving.locationAfter.x = myGame->boardSize -1;
						myMoving.locationAfter.y = 0;
						return myMoving;
					}


					location bckp = goAhead(down_left,myGame->lastLocationOfUser2);
					myBridge.left = bckp;
					bckp = goAhead(down_right,myGame->lastLocationOfUser2);
					myBridge.right = bckp;
					myGame->bridges.push_back(myBridge);

					location backup = myGame->firstLocationOfUser2;
					myGame->firstLocationOfUser2 = myGame->lastLocationOfUser2;
					myGame->lastLocationOfUser2 = backup;
					myGame->lastMovementOfUser2 = up;								// !!!!!! buraya sonsuz döngüye girmemesi için bi şey koy bi up bi down olacak
					return move(myGame);
					}

					if(myGame->lastLocationOfUser2.x == myGame->boardSize -1 && myGame->lastMovementOfUser2 != up){						// alt border'ı tamamladıysa diğerine doğru git
					location backup = myGame->firstLocationOfUser2;
					myGame->firstLocationOfUser2 = myGame->lastLocationOfUser2;
					myGame->lastLocationOfUser2 = backup;
					myGame->lastMovementOfUser2 = up;
					return move(myGame);
					}

				if(myGame->lastLocationOfUser2.x == 1 && myGame->lastMovementOfUser2 != down){					// üst border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.

					if(myLocation.y == myGame->boardSize-1)
					{
						myMoving.direction = up_left;
						myMoving.locationAfter.x = 0;
						myMoving.locationAfter.y = myGame->boardSize -1;
						return myMoving;
					}


					myBridge.left.x = 0;
					myBridge.left.y = myGame->lastLocationOfUser2.y;
					myBridge.right.x = 0;
					myBridge.right.y = myGame->lastLocationOfUser2.y +1;
					myGame->bridges.push_back(myBridge);
					location backup = myGame->firstLocationOfUser2;
					myGame->firstLocationOfUser2 = myGame->lastLocationOfUser2;
					myGame->lastLocationOfUser2 = backup;
					myGame->lastMovementOfUser2 = down;
					return move(myGame);
				}

				if(myGame->lastLocationOfUser2.x == 0 && myGame->lastMovementOfUser2 != up){						// üst border ı tamamladıysa diğerine doğru git
					location backup = myGame->firstLocationOfUser2;
					myGame->firstLocationOfUser2 = myGame->lastLocationOfUser2;
					myGame->lastLocationOfUser2 = backup;
					myGame->lastMovementOfUser2 = down;
					return move(myGame);
				}

				if(myGame->lastMovementOfUser2 == no){									// yön belirleme için
					if(myGame->lastLocationOfUser1.x <= myGame->lastLocationOfUser2.x)				// son hamle rakibin hamlesinin üstünde ise
					{
						movement mvmnts[]={up,up_2nd_right,up_2nd_left} ;
						for(movement m : mvmnts){
							myLocation = goAhead(m,myGame->lastLocationOfUser2);						
							myBridge = findBridge(myLocation,myGame->lastLocationOfUser2);
							if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = myGame->lastLocationOfUser2.x > myGame->firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								else if(!isLocationEmpty(myBridge.right,myGame), !isUserLocationOwner(myBridge.left,myGame) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = myGame->lastLocationOfUser2.x > myGame->firstLocationOfUser2.x ? down : up; 
										return myMoving;
									}

								else if(isLocationEmpty(myLocation,myGame) && myBridge.left.x != -1 && myBridge.right.x != -1 )
								{
									myMoving.direction = m;
									break;	
								}
						}
						myMoving.locationAfter = myLocation;
					}
					else 
					{
						movement mvmnts[]={down,down_2nd_right,down_2nd_left} ;
							for(movement m : mvmnts){
								myLocation = goAhead(m,myGame->lastLocationOfUser2);						
								myBridge = findBridge(myLocation,myGame->lastLocationOfUser2);
								if(isLocationEmpty(myLocation,myGame) && myBridge.left.x != -1 && myBridge.right.x != -1 )
								{
									myMoving.direction = m;
									break;			
								}				
							}
							myMoving.locationAfter = myLocation;
					}
					myGame->bridges.push_back( myBridge);			// bridge kontrolu yap !!
					return myMoving; 
				}
				
				else																							// yön belirli ise
				{	
				//	short range = 0;						// !! yukarı ise
					list<movement> upDirections = {up,up_2nd_left,up_2nd_right,up_left,up_rght,lft,rght};					// yön sıralaması
					list<movement> downDirections= {down,down_2nd_right,down_2nd_left,down_right,down_left,rght,lft};
					list<movement>directions; 
					if(myGame->lastMovementOfUser2 == rght || myGame->lastMovementOfUser2 == lft){							// yön sağ veya sol ise yukarı mı aşağı mı gidileceği belirlenir.
						if(myGame->lastLocationOfUser2.x > myGame->firstLocationOfUser2.x)
							directions = downDirections;
						else
							directions = upDirections;
					}
					else
						{
							if( isContainsDirection(upDirections,myGame->lastMovementOfUser2) )
								directions = upDirections;
							else
								directions = downDirections;
						}
					for(movement direction : directions)
					{
						myLocation = goAhead(movement(direction),myGame->lastLocationOfUser2);
						if(isLocationEmpty(myLocation,myGame) && isLocationCorrect(myLocation,myGame->boardSize) ){
							if(direction == up_2nd_right || direction == up_2nd_left || direction == up || direction == down || direction == down_2nd_left || direction == down_2nd_right)
							{
								myBridge = findBridge(myGame->lastLocationOfUser2,myLocation);
								if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = myGame->lastLocationOfUser2.x > myGame->firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = myGame->lastLocationOfUser2.x > myGame->firstLocationOfUser2.x ? down : up; 
										return myMoving;
									}
								
								if(isLocationCorrect(myBridge.left,myGame->boardSize) && isLocationCorrect(myBridge.right,myGame->boardSize) && isLocationEmpty(myLocation,myGame) && isLocationEmpty(myLocation,myGame))
								{
										myGame->bridges.push_back(myBridge);
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
					uniform_int_distribution<> distr(0,myGame->boardSize-1);
					location rand_location;
					rand_location.x = gen();
					rand_location.y = gen();
				}
				return myMoving;
			}

int main(){

    game hexGame= menu();
	display(&hexGame);
	while(!hexGame.isFinished){

		try	{
				int locationSize = hexGame.boardSize * hexGame.boardSize /2;
				location myLocation;
				moving myMoving;
				location ScannedLocations[locationSize];

				if(hexGame.playerTurn == 1 || hexGame.user2 != DEFAULT_NAME ){					// sıra user 1 de veya ikili oynanırken iken
					myLocation = takeLocation(&hexGame);
					if(isLocationCorrect(myLocation,hexGame.boardSize) && isLocationEmpty(myLocation,&hexGame)){
						play(&hexGame, myLocation);
						if(hexGame.firstLocationOfUser1.x == -1)
						hexGame.firstLocationOfUser1 =myLocation;
					}
					else
						{
						cerr << "You entered wrong location please enter again\n";
						continue; 
					}
				}
				else
					{
						if(hexGame.firstLocationOfUser2.x == -1)						// ilk oynayışı ise
							myLocation = firstMovement(&hexGame);
						else
							{
								myMoving = move(&hexGame);
								myLocation = myMoving.locationAfter;
							}
						if(!isLocationEmpty(myLocation,&hexGame) && !isLocationCorrect(myLocation,hexGame.boardSize))
							continue;
						else
						{
							if(!myMoving.isItBridging)												// normal ilerleme ise
							{
								hexGame.lastLocationOfUser2 = myLocation;
								hexGame.lastMovementOfUser2 = myMoving.direction;			
								play(&hexGame,myLocation);	
							}
							else																	// ara noktaları dolduruyorsa
								play(&hexGame,myLocation);	
							
						}
					}
			//	if(isOnOwnBorder(myLocation,&hexGame))
					if( isPathCompleted(myLocation,&hexGame,ScannedLocations) )		
						{
							hexGame.isFinished=true; 
							hexGame.winner = hexGame.playerTurn == 1 ? hexGame.user1 : hexGame.user2;
						}
				changePlayer(&hexGame);
			}

		catch(int e){
				if(e == 20)
					cerr << "You entered wrong location please enter it again";
				else
					cerr << "There is unknown error";
		}

		display(&hexGame);
	}

	showResults(&hexGame);

	return 0;
}
