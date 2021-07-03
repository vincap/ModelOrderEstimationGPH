/*
* COPYRIGHT NOTICE
*
* Pattern.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/
#pragma once

#include <vector>

/**
	The Pattern class is used to represent a pattern within the Dataset class.
	It provides read/write access to its features.
*/
class Pattern {

public :

	Pattern( unsigned int dimensionality );

	double &featureAt( unsigned int featureIndex );

	const double &featureAt( unsigned int featureIndex ) const;

	unsigned int getDimensionality() const;

private :

	unsigned int dimensionality;

	std::vector<double> featuresContainer;
};
