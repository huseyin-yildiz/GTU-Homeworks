#ifndef HEX_H_
#define HEX_H_
#include<iostream>
#include<list>
#include<string>
#include<random> 
#include<fstream>
#include<vector>


//	const auto PATHLIMIT = 30;
    const auto DEFAULT_NAME = "Computer";
	const auto MAX_CHILD_SIZE = 30;
    const auto MAX_BOARD_SIZE = 12;
	const auto DEEPNESS = 3;
    const auto MAX_PATH_SIZE = 30;


   	enum Movement{no,up,down,rght,lft,up_rght,up_left,down_right,down_left,up_2nd_right,up_2nd_left,down_2nd_right,down_2nd_left};		// enum for directions



	class Location
	{
		private:
				int x;
				int y;
		public:
				Location();
				Location(int x, int y);
				void setLocation(int x_, int y_){	x=x_; y=y_;	}
				void set_x(int x_);
				void set_y(int y_);
				inline int get_y()const;
				inline int get_x()const;
				void setByAdding(int x_, int y_);
				Location changeLocation(int x_,int y_);			// const function yap
				friend std::istream& operator>> (std::istream& in, Location location);

				bool operator==(Location another)const;
	};
	
	enum CellState
	{
		nope = ' '
		,user1 = 'o'
		,user2 = 'x'
		,dot = '.'
	};
	
	class Moving							// a struct for defining the moving (location before moving etc.)
	{
		public:
			Movement direction= no;
			Location locationBefore, locationAfter;
			bool isItBridging=false;
	};
	
	class Bridge{
	public:
		Location left,right;
		Bridge();
		Bridge(Location _left, Location _right);
		void set(Location _left, Location _right);
		const Bridge get();

		friend std::istream& operator>> (std::istream& in, std::list <Bridge> bridges);
	};
	



	
	
	// These functions is for general struct of the game and they are commented on the hex.cpp file
	
	class Hex	
	{

	private:

			class Cell {				// private 
			private:
				Location location;
				CellState cellState;



			public:
				Cell(int x, int y, CellState state);
				inline CellState getCellState() { return cellState; }
				void setState(CellState cs) { cellState = cs; }
				void setState(char cs) {
					if (cs == CellState::nope)
						cellState = CellState::nope;
					if (cs == CellState::user1)
						cellState = CellState::user1;
					if (cs == CellState::user2)
						cellState = CellState::user2;
					if (cs == CellState::dot)
						cellState = CellState::dot;
					//		else
					//			std::cerr <<"Wrong cell State";


				}

			};

	public:
		static int gameNow,compare1,compare2;
		static bool newGame;
		int boardSize,width,height;
		std::vector<std::vector<Cell>> matrix;				
		short playerTurn = 1;

		inline short getPlayerTurn() { return playerTurn; }
		std::string user1, user2 = DEFAULT_NAME, winner = "";
		bool isFinished = false;
    	Location lastLocationOfUser1,lastLocationOfUser2,firstLocationOfUser1,firstLocationOfUser2;
    	std::list<Bridge> bridges;
    	Movement lastMovementOfUser1 = Movement::no ,lastMovementOfUser2 = no;
    		

    		//Hex();
			void PlayGame();
			void clearScreen();
    		void createMatrix();
    		void display();
    		void play(Location myLocation);
    		bool loadSavedGame(std::string fileName);
    		bool saveGame(std::string fileName);
    		bool isPathCompleted (Location myLocation, std::vector<Location> & scannedLocations);			// checks if Path is completed or not
			void changePlayer();
			void showResults();
   			bool isLocationEmpty(Location myLocation);
   			void menu();
			void play();
			int getWidth();
			int getHeight();
			bool isGameEnded();			// !! not const
			int numberOfMarkedCells();
			static int MarkedCellsOfAllBoards( std::vector<Hex> & hexGames);
			bool isMarkedCellsMore(Hex & anotherHex) ;
			bool isLocationCorrect(Location myLocation);
			Location takeLocation();																				// takes a Location or SAVE-LOAD command from the user
	//		static void displayAllGames(std::vector<Hex> games);
    	
	private:
    		int getBoardSize();
    		bool isBordersConnected(std::vector<Location> scannedLocations);
			bool isUserLocationOwner(Location myLocation);
			bool isOnOwnBorder(Location myLocation);							// aldığı konumun kendi sınırlarında olup olmadığını bulur.
			bool isInScanned( Location myLocation, std::vector<Location> scannedLocations );
			void addToScannedLocations(Location newLocation, std::vector<Location> scannedLocations);
			std::list<Location> findConnections(Location myLocation);														// shows which user is winner
			Location goAhead(Movement myMovement,Location fromThis);							
			Bridge findBridge(const Location firsLocation,const Location secondLocation);							
			Moving move();
			bool isContainsDirection(std::list<Movement> directions, Movement direction);
			Location firstMovement();								
			std::list<Location> findConnections(Location myLocation,short boardSize);
    		CellState getStateForPlayerNow() {	 return (playerTurn == 2 ? CellState::user2 : CellState::user1 );	}


      };
      
      


#endif
