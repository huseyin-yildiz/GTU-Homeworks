#include "Location.h"

Location::Location()
{
    setLocation(-1, -1);
}

Location::Location(int x, int y)
{
    setLocation(x, y);
}

void Location::set_x(int x_)
{
    x = x_;
}

void Location::set_y(int y_)
{
    y = y_;
}

int Location::get_y() const
{
    return y;
}

int Location::get_x() const
{
    return x;
}

void Location::setByAdding(int x_, int y_)
{
    x += x_;
    y += y_;
}

Location Location::changeLocation(int x_, int y_)
{
    Location newLocation;
    newLocation.set_x(x + x_);
    newLocation.set_y(y + y_);
    return newLocation;
}

bool Location::operator==(Location another) const
{
    return (x == another.get_x() && y == another.get_y());
}

std::istream& operator>>(std::istream& in, Location location)
{
    int a, b;
    in >> a;
    in >> b;
    location.set_x(a);
    location.set_y(b);
    return in;
}
