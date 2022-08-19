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



	class Location												// a class for holding locations
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
	
	enum CellState										//enum for cellstate
	{
		nope = ' '
		,user1 = 'o'
		,user2 = 'x'
		,dot = '.'
	};
	
	


	
	
	// These functions is for general struct of the game and they are commented on the hex.cpp file
	
	class Hex	
	{
	private:
		

	public:
		int steps = 0;
		std::string fName;
			class Cell {				 
			private:
				Location location;
				CellState cellState;

			public:
				explicit Cell(int x, int y, CellState state);
				Cell();
			
				inline Location getLocation();
				inline CellState getCellState() { return cellState; }
				void setState(CellState cs) { cellState = cs; }
				void setLocation(int x, int y) { location.setLocation(x, y); }
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

	
		static int gameNow,compare1,compare2;
		static bool newGame;
		int boardSize,width,height;
	private:
		class CellMatrix						// a class for matrix including some constructors , pointers, overloaded operators 
		{

		private:
			typedef Cell* row;					// type for rows
			row* matrix;						// game matrix 
			int size=0;

		public:
			CellMatrix(int boardSize);															// creates matrix (constructor)
			CellMatrix();
			CellMatrix(const CellMatrix& other);											// copy constructor
			CellMatrix& operator=(const CellMatrix rValue);									// assignment operator overloading
			int getSize() const;
			row& operator[](int i) const;
			~CellMatrix();
		};

	public:

		CellMatrix matrix = CellMatrix();
		short playerTurn = 1;
		int score1 = 0, score2 = 0;																				// some required variables
		inline short getPlayerTurn() { return playerTurn; }															
		std::string user1, user2 = DEFAULT_NAME, winner = "";
		bool isFinished = false;
    	Location lastLocationOfUser1,lastLocationOfUser2,firstLocationOfUser1,firstLocationOfUser2;
    	Movement lastMovementOfUser1 = Movement::no ,lastMovementOfUser2 = no;
    		

    		Hex();
			bool PlayGame();																						// starts the game and main function of the game
			void clearScreen();
    		void createMatrix();
			friend std::ostream & operator <<(std::ostream & op, Hex & game);										// for displaying and saving the last situation of the board				
			friend bool operator >> (std::ifstream & is, Hex & game);											// for loading saved game
			void play(Location myLocation);
			void changePlayer();																				// change the player turn

			bool pTest(Location current, std::list<Location> & scannedLocations);

			void showResults();																					// shows the winner and points
   			bool isLocationEmpty(Location myLocation);
   			void menu();
			void play();																	
			int getWidth();
			int getHeight();
			bool isGameEnded();			// !! not const
			int numberOfMarkedCells();
			static int MarkedCellsOfAllBoards( std::vector<Hex> & hexGames);					// it takes all hex games at main function
			bool isMarkedCellsMore(Hex & anotherHex) ;
			bool isLocationCorrect(Location myLocation);
			Location takeLocation();																				// takes a Location or SAVE-LOAD command from the user
			void operator ==(Hex& other);
			void deleteTheTempFiles( );									
    	
	private:
		
    		int getBoardSize();
			bool isUserLocationOwner(Location myLocation);
			bool isOnOwnBorder(Location myLocation);							// aldığı konumun kendi sınırlarında olup olmadığını bulur.
			bool saveGame(std::string fileName);
			std::list<Location> findConnections(Location myLocation);			// finds all neighbours of a location													
			Location goAhead(Movement myMovement,Location fromThis);							
			Location move();
			bool isContainsDirection(std::list<Movement> directions, Movement direction);
			Location firstMovement();															// selects a location for computers first playing
			std::list<Location> findConnections(Location myLocation,short boardSize);
    		CellState getStateForPlayerNow() {	 return (playerTurn == 2 ? CellState::user2 : CellState::user1 );	}
			bool evaluateScore(short user);
			Hex operator--();													// pre decreament (undo function)
			Hex & operator--(int i);												// post decreament (undo function)

      };
      
      


#endif
