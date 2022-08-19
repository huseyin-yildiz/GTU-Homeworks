#pragma once
#include "AbstractHex.h"

namespace Hex
{
	template<typename T = CellState, typename R = vector<T> >
	class HexAdapter : public AbstractHex
	{

	public:
		HexAdapter(int boardSize, string user1, string user2);
		void setSize(int size) throw(my_exception) final;  // throws string
		void reset() final;
		void play(Location location) final;
		void play() final;
		CellState& operator()(int i, int j) throw(out_of_board_exception) final;

	private:
		R matrix;
	};

	template<typename T, typename R>
	HexAdapter<T, R>::HexAdapter(int boardSize, string user1, string user2) : AbstractHex(user1, user2)
	{
		setSize(boardSize);
	}



	template<typename T, typename R>
	void HexAdapter<T, R>::setSize(int size) throw(my_exception)
	{
		matrix.clear();

		if (size > 5 && size < 32)
		{
			for (int i = 0; i < size; i++)
			{
				typename R::value_type row;
				for (int j = 0; j < size; j++)
					row.push_back(CellState::dot);
				matrix.push_back(row);

			}
			boardSize = size;
		}
		else
			throw my_exception("size must be larger than 5 and smaller than 32");
	}

	template<typename T, typename R>
	void HexAdapter<T, R>::reset()
	{
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				matrix[i][j] = CellState::dot;
	}

	template<typename T, typename R>
	void HexAdapter<T, R>::play(Location location)
	{
		if (playerTurn == 1)																// if user turn is 1 
			matrix[location.get_x()][location.get_y()] = (CellState::user1);

		else if (playerTurn == 2)
			matrix[location.get_x()][location.get_y()] = (CellState::user2); 				// if turn is 2	

		lastLocation = location;
		numberOfSteps++;
		changePlayerTurn();
	}

	template<typename T, typename R>
	void HexAdapter<T, R>::play()
	{
		if (playerTurn == 1)																// checking if player turn is 2 or not 
			throw my_exception("This is from play() function: player turn is not 2. Computer can not play now.");

		vector<Location> freeCells;
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)								// finds free cells
				if (matrix[i][j] == CellState::dot)
					freeCells.push_back(Location(i, j));


		default_random_engine defEngine;
		uniform_int_distribution<int> intDistro(0, freeCells.size());					// selects one of them
		int randomIndex = intDistro(defEngine);

		play(freeCells.at(randomIndex));
	}

	template<typename T, typename R>
	CellState& HexAdapter<T, R>::operator()(int i, int j) throw(out_of_board_exception)
	{
		if (i >= boardSize || j >= boardSize)
			throw out_of_board_exception();
		else
			return matrix[i][j];
	}

}