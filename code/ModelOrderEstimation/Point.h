/*
* COPYRIGHT NOTICE
*
* Point.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include <cmath>

class Point {

public :

	Point(double x, double y) : x(x), y(y) {}

	inline double getX() const { return x; }

	inline double getY() const { return y; }

	inline double norm2() const { return std::sqrt(x*x + y*y); }

private :

	double x, y;
};
