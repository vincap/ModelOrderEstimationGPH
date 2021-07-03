/*
* COPYRIGHT NOTICE
* 
* TimeSeries.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include <vector>

class TimeSeries {

public:

	TimeSeries();

	void appendValue( double value );

	double &valueAt( unsigned int index );

	const double &valueAt( unsigned int index ) const;

	unsigned int getSize() const;

	void clear();

	~TimeSeries();

private :

	std::vector<double> baseContainer;
};