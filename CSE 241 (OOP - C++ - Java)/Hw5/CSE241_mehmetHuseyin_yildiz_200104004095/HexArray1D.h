#pragma once


#include "AbstractHex.h"

namespace Hex
{
	class HexArray1D : public AbstractHex
	{
	public:
		HexArray1D(int boardSize, string user1, string user2);			// constructor
		HexArray1D(const HexArray1D& another);							// copy constructor
		const HexArray1D& operator=(const HexArray1D& another);			// assignment operator
		~HexArray1D();													// destructor

		void setSize(int size) final;
		void reset() final;
		void play(Location location) final;
		void play() final;
		CellState& operator() (int i, int j) ;

	private:
		CellState* matrix;
	};
}