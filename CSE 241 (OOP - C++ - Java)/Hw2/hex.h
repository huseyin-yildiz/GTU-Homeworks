#include<string>
#include<list>
#ifndef HEX_H_		
#define HEX_H_

	const auto PATHLIMIT = 30;
    const auto DEFAULT_NAME = "Computer";
    const auto MAX_BOARD_SIZE = 12;
    const auto MAX_PATH_SIZE = 30;
	const auto MAX_CHILD_SIZE = 30;
	const auto DEEPNESS = 3;


    struct location								// a struct for location x and y
	{
		int x=-1;
		int y=-1;
	};

	struct  bridge							
	{
		location left,right;
	};

	enum movement{no,up,down,rght,lft,up_rght,up_left,down_right,down_left,up_2nd_right,up_2nd_left,down_2nd_right,down_2nd_left};		// struct for directions
	enum cellState{
		nope = ' '
		,user1 = 'o'
		,user2 = 'x'
		,dot = '.'
	};
	struct moving							// a struct for defining the moving (location before moving etc.)
	{
		movement direction;
		location locationBefore, locationAfter;
		bool isItBridging=false;
	};
	
      struct game	
      {
        int boardSize;
        std::string user1, user2 = DEFAULT_NAME, winner = "";              
		char matrix [MAX_BOARD_SIZE][MAX_BOARD_SIZE];
		bool isFinished = false;
    	short playerTurn=1;
    	location lastLocationOfUser1,lastLocationOfUser2,firstLocationOfUser1,firstLocationOfUser2;
    	std::list<bridge> bridges;
    	movement lastMovementOfUser1 = no,lastMovementOfUser2 = no;
      };


// These functions is for general struct of the game and they are commented on the hex.cpp file

bool saveGame(game & myGame, std::string fileName);				
bool loadSavedGame(std::string fileName,game & myGame);
void createMatrix(game & myGame);
void clearScreen();
void display(const game & myGame);
void play(game & myGame,location myLocation);
bool isLocationCorrect(const location myLocation,const int boardSize);															
bool isLocationEmpty(const location myLocation,const game & myGame);
location takeLocation(game & myGame);
game menu();
bool isOnOwnBorder(location myLocation, game & myGame);     		
bool isUserLocationOwner(location myLocation,game & myGame);                
bool isInScanned(const location myLocation,const location scannedLocations[] );
void addToScannedLocations(location newLocation,location* scannedLocations,int* locationSize);
bool isBordersConnected(location* scannedLocations, short user,short bordSize);
location setLocation(location myLocation, int x = -1, int y = -1);
bool isPathCompleted (location myLocation,game & myGame, location scannedLocations[]);
void changePlayer(game & myGame);
void showResults(game & myGame);


#endif
