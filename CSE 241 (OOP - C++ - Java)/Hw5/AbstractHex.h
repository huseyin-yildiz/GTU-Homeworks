#ifndef ABSTRACTHEX_H_
#define ABSTRACTHEX_H_

#include<iostream>

using namespace std;

class AbstractHex
{
public:
    enum CellState										//enum for cellstate
    {
        nope = ' '
        , user1 = 'o'
        , user2 = 'x'
        , dot = '.'
    };
    
    virtual void print() = 0;
    virtual void readFromFile() = 0;
    virtual void reset() = 0;
    virtual void setSize(int size) = 0;
    virtual void play() = 0;
    virtual void play(CellState cellstate);
    virtual void isEnd() = 0;
    virtual CellState operator[](int i) = 0;
    virtual CellState lastMove() = 0;// throw exception("There is no last move.") = 0;
    virtual int numberOfMoves() = 0;
    
};

#endif