#pragma once
#include <stdexcept>
#include <exception>

class out_of_board_exception : public std::exception
{
public:
	out_of_board_exception() : exception()
	{
		// intentionally empty;
	}

	virtual const char* what() const throw()
  {
    return "Tried to access out of board.";
  }
};