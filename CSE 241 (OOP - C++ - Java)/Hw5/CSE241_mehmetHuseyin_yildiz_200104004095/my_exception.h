#pragma once
#include <stdexcept>
#include <exception>
#include <string>

class my_exception : public std::exception
{
public:
	my_exception(std::string msg) : exception()
	{
        message = msg;
	}

	virtual const char* what() const throw()
  {
    return message.c_str();
  }

private:
    std::string message;
};