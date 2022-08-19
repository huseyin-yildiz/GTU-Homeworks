#include "HexArray1D.h"

namespace Hex
{
	HexArray1D::HexArray1D(int boardSize, string user1, string user2) : AbstractHex(user1, user2)
	{
		setSize(boardSize);
	}

	HexArray1D::HexArray1D(const HexArray1D& another) : HexArray1D(another.boardSize,another.username1,another.username2)
	{
		boardSize = another.boardSize;
		isEnded = another.isEnded;
		lastLocation = another.lastLocation;
		numberOfSteps = another.numberOfSteps;
		playerTurn = another.playerTurn;
		username1 = another.username1;
		username2 = another.username2;
		setSize(boardSize);
		for (int i = 0; i < boardSize * boardSize; i++)
			matrix[i] = another.matrix[i];
	}


	
	const HexArray1D& HexArray1D::operator=(const HexArray1D& another)
	{
		boardSize = another.boardSize;
		isEnded = another.isEnded;
		lastLocation = another.lastLocation;
		numberOfSteps = another.numberOfSteps;
		playerTurn = another.playerTurn;
		username1 = another.username1;
		username2 = another.username2;
		setSize(boardSize);
		for (int i = 0; i < boardSize * boardSize; i++)
			matrix[i] = another.matrix[i];
		return another;
	}

	HexArray1D::~HexArray1D()
	{
		free(matrix);
	}

	void HexArray1D::setSize(int size) 
	{
		if (size < 5 || size > 32)
			throw my_exception("size must be larger than 5 and smaller than 32");
		else 
		{
			free(matrix);
			matrix = (CellState*)calloc(size * size, sizeof(CellState));							// allocates some places for board
			boardSize = size;
			reset();
		}
	}

	void HexArray1D::reset()
	{
		for (int i = 0; i < (boardSize * boardSize); i++)													// filling the matrix with cellstate dot
			matrix[i] = CellState::dot;
	}

	void HexArray1D::play(Location location)
	{
		int index = (location.get_x() * boardSize) + location.get_y();				// calculating the index
		if (playerTurn == 1)														// if user turn is 1 
			matrix[index] = (CellState::user1);

		else if (playerTurn == 2)
			matrix[index] = (CellState::user2); 									// if turn is 2	

		lastLocation = location;
		numberOfSteps++;
		changePlayerTurn();
	}

	void HexArray1D::play()
	{
		

		vector<Location> freeCells;
		for (int i = 0; i < (boardSize * boardSize); i++)									// finds free cells
			if (matrix[i] == CellState::dot)
				freeCells.push_back(Location(i / boardSize, i % boardSize));


		default_random_engine defEngine;
		uniform_int_distribution<int> intDistro(0, freeCells.size());					// selects one of them
		int randomIndex = intDistro(defEngine);

		play(freeCells.at(randomIndex));
	}

	CellState& HexArray1D::operator()(int i, int j)
	{
		int index = i * boardSize + j;
		if (i >= boardSize || j >= boardSize)
			throw out_of_board_exception();
		else
			return matrix[index];
	}
}