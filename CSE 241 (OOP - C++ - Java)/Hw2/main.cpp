#include<iostream>
#include"hex.h"
#include"hexPlayer.h"

using namespace std;



int main(){

    game hexGame= menu();
	display(hexGame);
	while(!hexGame.isFinished){													// the game keeps going while the game is not finished.

		try	{
				int locationSize = hexGame.boardSize * hexGame.boardSize /2;
				location myLocation;
				moving myMoving;
				location ScannedLocations[locationSize];

				if(hexGame.playerTurn == 1 || hexGame.user2 != DEFAULT_NAME ){					// sıra user 1 de veya ikili oynanırken
						myLocation = takeLocation(hexGame);
					
					if(isLocationCorrect(myLocation,hexGame.boardSize) && isLocationEmpty(myLocation,hexGame)){
						play(hexGame, myLocation);
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
							myLocation = firstMovement(hexGame);
						else
							{
								myMoving = move(hexGame);
								myLocation = myMoving.locationAfter;
							}
						if(!isLocationEmpty(myLocation,hexGame) && !isLocationCorrect(myLocation,hexGame.boardSize))
							continue;
						else
						{
							if(!myMoving.isItBridging)												// normal ilerleme ise
							{
								hexGame.lastLocationOfUser2 = myLocation;
								hexGame.lastMovementOfUser2 = myMoving.direction;			
								play(hexGame,myLocation);	
							}
							else																	// ara noktaları dolduruyorsa
								play(hexGame,myLocation);	
							
						}
					}

					if( isPathCompleted(myLocation,hexGame,ScannedLocations) )				// if the path is completed then sets the winner.
						{
							hexGame.isFinished=true; 
							hexGame.winner = hexGame.playerTurn == 1 ? hexGame.user1 : hexGame.user2;
						}
				changePlayer(hexGame);														// changes the user now at last.
			}

		catch(int e){
				if(e == 20)
					cerr << "You entered wrong location please enter it again";
				else
					cerr << "There is unknown error";
		}

		display(hexGame);												// displays the board after every playing.
	}

	showResults(hexGame);												// shows the winner

	return 0;
}
