/*
* COPYRIGHT NOTICE
*
* Pattern.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "Pattern.h"

#include <string>
#include <stdexcept>

Pattern::Pattern( unsigned int dimensionality ) : featuresContainer( dimensionality, 0.0 )
{
	this->dimensionality = dimensionality;
}

double & Pattern::featureAt( unsigned int featureIndex )
{
	if( featureIndex > dimensionality )
		throw std::out_of_range( "Cannot access feature number " + std::to_string( featureIndex ) + " from a pattern of dimensionality " + std::to_string( dimensionality ) );

	return featuresContainer.at( featureIndex );
}

const double & Pattern::featureAt( unsigned int featureIndex ) const
{
	if( featureIndex > dimensionality )
		throw std::out_of_range( "Cannot access feature number " + std::to_string( featureIndex ) + " from a pattern of dimensionality " + std::to_string( dimensionality ) );

	return featuresContainer.at( featureIndex );
}

unsigned int Pattern::getDimensionality() const { return dimensionality; }
