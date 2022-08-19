#ifndef HEXVECTOR_H_
#define HEXVECTOR_H_


#include<iostream>
#include"AbstractHex.h"
#include<vector>

using namespace std;


class HexVector : public AbstractHex
{
public:
    virtual void setSize(int size) final;
  

private:
    vector< vector<CellState> > matrix;


};


#endif