/*
* COPYRIGHT NOTICE
*
* Dataset.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "../TimeSeries/TimeSeries.h"
#include "Pattern.h"

/**
	The Dataset class represents a collection of examples.
	Each example is a pair (pattern, target).
	A Dataset object is essentially a Nx(D+1) matrix, where
	N is the number of stored examples and D is the pattern dimensionality.
	Each row is an examples. Last column of each row always represents the target associated to the corresponding pattern.
*/
class Dataset {

public :

	Dataset( unsigned int patternsDimensionality );

	Dataset( unsigned int patternsDimensionality, const TimeSeries &timeSeries );

	~Dataset();

	void getExampleAt( unsigned int exampleIndex, double &target, Pattern &pattern ) const;

	void addExample( double target, const Pattern &pattern );

	unsigned int getSize() const;

	unsigned int getPatternsDimensionality() const;

	void clearDataset();

private :

	double getValueAt( unsigned int exampleIndex, unsigned int valueIndex ) const;

	void setValueAt( unsigned int exampleIndex, unsigned int valueIndex, double newValue );

	void ensureAllocationNeeds();

	void initializeDatasetFromTimeSeries(const TimeSeries &timeSeries);

	double *linearizedDataset;

	unsigned int examplesNum, patternsDimensionality, numAllocatedExamples;

	const unsigned int INITIAL_ALLOCATED_EXAMPLES = 100, REALLOC_EXAMPLES_AMOUNT = 100;

	unsigned int exampleByteLength;
};
