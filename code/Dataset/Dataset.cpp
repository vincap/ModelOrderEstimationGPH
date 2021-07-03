/*
* COPYRIGHT NOTICE
*
* Dataset.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "Dataset.h"

#include <string>
#include <iostream>

Dataset::Dataset( unsigned int patternsDimensionality )
{
	this->patternsDimensionality = patternsDimensionality;

	// Size of pattern+target.
	exampleByteLength = sizeof( double )*( patternsDimensionality + 1 );

	examplesNum = 0;

	linearizedDataset = (double*)malloc( INITIAL_ALLOCATED_EXAMPLES*exampleByteLength );

	if( linearizedDataset == NULL )
		throw std::bad_alloc();

	numAllocatedExamples = INITIAL_ALLOCATED_EXAMPLES;
}

Dataset::Dataset( unsigned int patternsDimensionality, const TimeSeries & timeSeries )
{
	this->patternsDimensionality = patternsDimensionality;

	exampleByteLength = sizeof( double )*( patternsDimensionality + 1 );

	initializeDatasetFromTimeSeries( timeSeries );
}

Dataset::~Dataset() { free( linearizedDataset ); }

void Dataset::getExampleAt( unsigned int exampleIndex, double & target, Pattern & pattern ) const
{
	if( exampleIndex >= examplesNum )
		throw std::out_of_range( "Example index out of range. Requested " + std::to_string(exampleIndex) + ", available " + std::to_string(examplesNum));

	if( pattern.getDimensionality() != patternsDimensionality )
		throw std::logic_error( "Output pattern's dimensionality (" + std::to_string( pattern.getDimensionality() ) + ") is not compatible with dataset dimensionality (" + std::to_string(patternsDimensionality) + ")." );

	for( int currFeatureIdx = 0; currFeatureIdx < patternsDimensionality; currFeatureIdx++ )
		pattern.featureAt( currFeatureIdx ) = this->getValueAt( exampleIndex, currFeatureIdx );

	target = this->getValueAt( exampleIndex, patternsDimensionality );
}

void Dataset::addExample( double target, const Pattern & pattern )
{
	if( pattern.getDimensionality() != patternsDimensionality )
		throw std::logic_error( "Input pattern's dimensionality (" + std::to_string( pattern.getDimensionality() ) + ") is not compatible with dataset dimensionality (" + std::to_string( patternsDimensionality ) + ")." );

	ensureAllocationNeeds();

	for( int currFeatureIdx = 0; currFeatureIdx < patternsDimensionality; currFeatureIdx++ )
		this->setValueAt( examplesNum, currFeatureIdx, pattern.featureAt( currFeatureIdx ) );

	this->setValueAt( examplesNum, patternsDimensionality, target );

	examplesNum++;
}

unsigned int Dataset::getSize() const { return examplesNum; }

unsigned int Dataset::getPatternsDimensionality() const { return patternsDimensionality; }

void Dataset::clearDataset()
{
	if( examplesNum != 0 ) {

		examplesNum = 0;

		numAllocatedExamples = 0;

		free( linearizedDataset );
	}
}

double Dataset::getValueAt( unsigned int exampleIndex, unsigned int valueIndex ) const
{
	return *( linearizedDataset + ( patternsDimensionality + 1 ) * exampleIndex + valueIndex );
}

void Dataset::setValueAt( unsigned int exampleIndex, unsigned int valueIndex, double newValue )
{
	*( linearizedDataset + ( patternsDimensionality + 1 ) * exampleIndex + valueIndex ) = newValue;
}

void Dataset::ensureAllocationNeeds()
{
	if( examplesNum == numAllocatedExamples ) {

		double *newTmpPtr = (double*)realloc( linearizedDataset, (numAllocatedExamples + REALLOC_EXAMPLES_AMOUNT )*exampleByteLength);

		if( newTmpPtr == NULL )
			throw std::bad_alloc();

		linearizedDataset = newTmpPtr;

		numAllocatedExamples += REALLOC_EXAMPLES_AMOUNT;
	}
}

void Dataset::initializeDatasetFromTimeSeries( const TimeSeries & timeSeries )
{
	examplesNum = timeSeries.getSize() - patternsDimensionality;

	linearizedDataset = (double*)malloc( examplesNum*exampleByteLength );

	if( linearizedDataset == NULL ) {

		examplesNum = 0;

		throw std::bad_alloc();
	}

	numAllocatedExamples = examplesNum;

	unsigned int currExampleIdx = 0;

	for( unsigned int currTargetIdx = patternsDimensionality; currTargetIdx < timeSeries.getSize(); currTargetIdx++ ) {

		unsigned int currDatasetValueIdx = 0;

		for( unsigned int currValueIdx = currTargetIdx - patternsDimensionality; currValueIdx <= currTargetIdx; currValueIdx++ ) {

			this->setValueAt( currExampleIdx, currDatasetValueIdx, timeSeries.valueAt( currValueIdx ) );

			currDatasetValueIdx++;
		}

		currExampleIdx++;
	}
}
