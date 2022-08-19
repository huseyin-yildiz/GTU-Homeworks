#include<iostream>
#include<list>
#include<string>
#include<random> 
#include<fstream>
#include"hex.h"
using namespace std;


			location goAhead(movement myMovement,location fromThis){							// belirtilen lokasyondan istenilen yönün lokasyonunu döndürür.
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

			location firstMovement(game & myGame){												// if this movement is first movement selects a locaton.
				random_device random;						
				mt19937 gen(random());
				location myLocation;
				short middle = myGame.boardSize/2;
				uniform_int_distribution<> distr(0,middle-1);

				if (myGame.lastLocationOfUser1.y > middle-1 )
					myLocation.y = myGame.lastLocationOfUser1.y - distr(gen);
				else
					myLocation.y = distr(gen);
				int difference = myGame.lastLocationOfUser1.y - myLocation.y;
				myLocation.x = myGame.lastLocationOfUser1.x + (difference < 0 ? -1*difference  : difference)*(2.0/3.0) ;
				if(!isLocationEmpty(myLocation,myGame) || myLocation.x == myGame.boardSize-1 )
					return firstMovement(myGame);
				myGame.firstLocationOfUser2 = myLocation;
				return myLocation;
			}

            bool isContainsDirection(list<movement> directions, movement direction)				// finds if given list has given direction or not
			{
				for(auto m : directions)					// burası da
				{
					if(direction == m)
					return true;
				}
				return false;
			}

			bridge findBridge(const location firsLocation,const location secondLocation){									// finds a bridge (points between two point)
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

            moving move(game & myGame)				// gives a location for playing
			{
				location myLocation;
				bridge myBridge;
				moving myMoving;
			//	list<bridge>::iterator it;
				myMoving.locationBefore = myGame.lastLocationOfUser2;

				if(myGame.bridges.size() > 0)
				for(auto it = myGame.bridges.begin(); it != myGame.bridges.end(); it++ )				// bridge lerden biri dolunursa diğerini alır.
					{
						if(myGame.matrix[(*it).left.x][(*it).left.y] == cellState::user1 )
							{
								myLocation.x = (*it).right.x;
								myLocation.y = (*it).right.y;
								myMoving.locationAfter = myLocation;
								myMoving.isItBridging = true;
								myGame.bridges.erase(it);

								return myMoving;
							}
						if(myGame.matrix[(*it).right.x][(*it).right.y] == cellState::user1){
							myLocation.x = (*it).left.x;
							myLocation.y = (*it).left.y;
							myMoving.locationAfter = myLocation;
							myMoving.isItBridging = true;
								myGame.bridges.erase(it);

								return myMoving;
						}
					}

					if( (myGame.lastLocationOfUser2.x >= myGame.boardSize -2 && myGame.firstLocationOfUser2.x <= 1) || (myGame.lastLocationOfUser2.x <=1 && myGame.firstLocationOfUser2.x >= myGame.boardSize -2) )		// iki tarafta border a yetişirse bridge leri doldur
					{	for( auto it = myGame.bridges.begin(); it != myGame.bridges.end(); it++){
							if( isLocationEmpty( bridge(*it).left,myGame ))
								{
									bridge dlt = *it;
									myGame.bridges.erase(it);
									myMoving.isItBridging = true;
									myMoving.locationAfter = dlt.left;
									return myMoving;
								}
							else
							{
								bridge dlt = *it;
								myGame.bridges.erase(it);
								myMoving.isItBridging = true;
								myMoving.locationAfter = dlt.right;
								return myMoving;
							}
							
						}		
					}
				if(myGame.lastLocationOfUser2.x == myGame.boardSize -2 && myGame.lastMovementOfUser2 != up )	// alt border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.
				{

					if(myLocation.y == 0)
					{
						myMoving.direction = down_right;
						myMoving.locationAfter.x = myGame.boardSize -1;
						myMoving.locationAfter.y = 0;
						return myMoving;
					}


					decltype(myLocation) bckp = goAhead(down_left,myGame.lastLocationOfUser2);
					myBridge.left = bckp;
					bckp = goAhead(down_right,myGame.lastLocationOfUser2);
					myBridge.right = bckp;
					myGame.bridges.push_back(myBridge);

					decltype(myLocation) backup = myGame.firstLocationOfUser2;
					myGame.firstLocationOfUser2 = myGame.lastLocationOfUser2;
					myGame.lastLocationOfUser2 = backup;
					myGame.lastMovementOfUser2 = up;								// !!!!!! buraya sonsuz döngüye girmemesi için bi şey koy bi up bi down olacak
					return move(myGame);
					}

					if(myGame.lastLocationOfUser2.x == myGame.boardSize -1 && myGame.lastMovementOfUser2 != up){						// alt border'ı tamamladıysa diğerine doğru git
					location backup = myGame.firstLocationOfUser2;
					myGame.firstLocationOfUser2 = myGame.lastLocationOfUser2;
					myGame.lastLocationOfUser2 = backup;
					myGame.lastMovementOfUser2 = up;
					return move(myGame);
					}

				if(myGame.lastLocationOfUser2.x == 1 && myGame.lastMovementOfUser2 != down){					// üst border a yetişmesine 1 adım kaldıysa diğer uçtan devam et.

					if(myLocation.y == myGame.boardSize-1)
					{
						myMoving.direction = up_left;
						myMoving.locationAfter.x = 0;
						myMoving.locationAfter.y = myGame.boardSize -1;
						return myMoving;
					}


					myBridge.left.x = 0;
					myBridge.left.y = myGame.lastLocationOfUser2.y;
					myBridge.right.x = 0;
					myBridge.right.y = myGame.lastLocationOfUser2.y +1;
					myGame.bridges.push_back(myBridge);
					location backup = myGame.firstLocationOfUser2;
					myGame.firstLocationOfUser2 = myGame.lastLocationOfUser2;
					myGame.lastLocationOfUser2 = backup;
					myGame.lastMovementOfUser2 = down;
					return move(myGame);
				}

				if(myGame.lastLocationOfUser2.x == 0 && myGame.lastMovementOfUser2 != up){						// üst border ı tamamladıysa diğerine doğru git
					location backup = myGame.firstLocationOfUser2;
					myGame.firstLocationOfUser2 = myGame.lastLocationOfUser2;
					myGame.lastLocationOfUser2 = backup;
					myGame.lastMovementOfUser2 = down;
					return move(myGame);
				}

				if(myGame.lastMovementOfUser2 == no){									// yön belirleme için
					if(myGame.lastLocationOfUser1.x <= myGame.lastLocationOfUser2.x)				// son hamle rakibin hamlesinin üstünde ise
					{
						movement mvmnts[]={up,up_2nd_right,up_2nd_left} ;
						for(auto m : mvmnts){											// burası da
							myLocation = goAhead(m,myGame.lastLocationOfUser2);						
							myBridge = findBridge(myLocation,myGame.lastLocationOfUser2);
							if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = myGame.lastLocationOfUser2.x > myGame.firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								else if(!isLocationEmpty(myBridge.right,myGame), !isUserLocationOwner(myBridge.left,myGame) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = myGame.lastLocationOfUser2.x > myGame.firstLocationOfUser2.x ? down : up; 
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
							for(auto m : mvmnts){									
								myLocation = goAhead(m,myGame.lastLocationOfUser2);						
								myBridge = findBridge(myLocation,myGame.lastLocationOfUser2);
								if(isLocationEmpty(myLocation,myGame) && myBridge.left.x != -1 && myBridge.right.x != -1 )
								{
									myMoving.direction = m;
									break;			
								}				
							}
							myMoving.locationAfter = myLocation;
					}
					myGame.bridges.push_back( myBridge);			// bridge kontrolu yap !!
					return myMoving; 
				}
				
				else																							// yön belirli ise
				{	
				//	short range = 0;						// !! yukarı ise
					list<movement> upDirections = {up,up_2nd_left,up_2nd_right,up_left,up_rght,lft,rght};					// yön sıralaması
					list<movement> downDirections= {down,down_2nd_right,down_2nd_left,down_right,down_left,rght,lft};
					list<movement>directions; 
					if(myGame.lastMovementOfUser2 == rght || myGame.lastMovementOfUser2 == lft){							// yön sağ veya sol ise yukarı mı aşağı mı gidileceği belirlenir.
						if(myGame.lastLocationOfUser2.x > myGame.firstLocationOfUser2.x)
							directions = downDirections;
						else
							directions = upDirections;
					}
					else
						{
							if( isContainsDirection(upDirections,myGame.lastMovementOfUser2) )
								directions = upDirections;
							else
								directions = downDirections;
						}
					for(auto direction : directions)									
					{
						myLocation = goAhead(movement(direction),myGame.lastLocationOfUser2);
						if(isLocationEmpty(myLocation,myGame) && isLocationCorrect(myLocation,myGame.boardSize) ){
							if(direction == up_2nd_right || direction == up_2nd_left || direction == up || direction == down || direction == down_2nd_left || direction == down_2nd_right)
							{
								myBridge = findBridge(myGame.lastLocationOfUser2,myLocation);
								if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame) )			// soldaki bridge'i rakip alır ise sağdakine git
									{
										if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame))
											continue;
										myMoving.locationAfter = myBridge.right;
										myMoving.direction = myGame.lastLocationOfUser2.x > myGame.firstLocationOfUser2.x ? down : up;
										return myMoving; 
									}
								if(!isLocationEmpty(myBridge.right,myGame) && !isUserLocationOwner(myBridge.right,myGame) )			// sağdaki bridge'i rakip alır ise soldakine git
									{
										if(!isLocationEmpty(myBridge.left,myGame) && !isUserLocationOwner(myBridge.left,myGame))
											continue;
										myMoving.locationAfter = myBridge.left;
										myMoving.direction = myGame.lastLocationOfUser2.x > myGame.firstLocationOfUser2.x ? down : up; 
										return myMoving;
									}
								
								if(isLocationCorrect(myBridge.left,myGame.boardSize) && isLocationCorrect(myBridge.right,myGame.boardSize) && isLocationEmpty(myLocation,myGame) && isLocationEmpty(myLocation,myGame))
								{
										myGame.bridges.push_back(myBridge);
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
					uniform_int_distribution<> distr(0,myGame.boardSize-1);
					location rand_location;
					rand_location.x = gen();
					rand_location.y = gen();
				}
				return myMoving;
			}

            list<location> findConnections(location myLocation,short boardSize)			// finds the Locations around a location 
			{
				list <location> connections;
				connections.push_back(myLocation);
				connections.push_back( setLocation(myLocation,-1,0) ); 
				connections.push_back( setLocation(myLocation,1,0) );	
				connections.push_back( setLocation(myLocation,0,-1) ); 
				connections.push_back( setLocation(myLocation,0,1) ); 
				connections.push_back( setLocation(myLocation,-1,1) );
				connections.push_back( setLocation(myLocation,1,-1) );
													
				for(auto it=connections.begin(); it != connections.end();it++)
					if( !isLocationCorrect(*it,boardSize) )
							connections.erase(it--);
						
				return connections;
			}