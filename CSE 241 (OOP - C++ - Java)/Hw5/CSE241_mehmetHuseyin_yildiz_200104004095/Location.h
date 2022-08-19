#pragma once
#include <fstream>
class Location
{
private:
	int x;
	int y;
public:
	Location();
	Location(int x, int y);
	void setLocation(int x_, int y_) { x = x_; y = y_; }
	void set_x(int x_);
	void set_y(int y_);
	int get_y()const;
	int get_x()const;
	void setByAdding(int x_, int y_);
	Location changeLocation(int x_, int y_);			// const function yap
	friend std::istream& operator>> (std::istream& in, Location location);

	bool operator==(Location another)const;
};

