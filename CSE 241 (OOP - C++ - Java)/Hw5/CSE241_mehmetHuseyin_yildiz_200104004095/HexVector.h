#pragma once

#include<iostream>
#include"AbstractHex.h"

using namespace std;

namespace Hex
{
    class HexVector : public AbstractHex
    {
    public:
        HexVector(int boardSize, string user1, string user2);
        void setSize(int size) throw(my_exception) final;  // throws string
        void reset() final;
        void play(Location location) final;
        void play() final;
        CellState& operator()(int i, int j) throw(out_of_board_exception) final ;

    private:
        vector< vector<CellState> > matrix;
    };
}