/*
* COPYRIGHT NOTICE
*
* LogLogPlot.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "Point.h"

#include <vector>
#include <string>

class LogLogPlot {

public :

	LogLogPlot() {}

	void appendPoint( const Point& point ) { baseContainer.push_back( point ); }

	Point getPoint( unsigned int index ) const { return baseContainer.at( index ); }

	unsigned int getSize() const { return baseContainer.size(); }

	void clear() { baseContainer.clear(); }

	static void readLogLogPlot( const std::string &inFilePath, LogLogPlot &llp );

	static void writeLogLogPlot( const std::string &outFilePath, const LogLogPlot &llp );

private :

	std::vector<Point> baseContainer;
};
