/*
* COPYRIGHT NOTICE
*
* LogLogPlotCalculator.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "LogLogPlotCalculator.h"
#include <iostream>

LogLogPlotCalculator::LogLogPlotCalculator( double minLogR, double maxLogR, unsigned int logRSteps )
{
	this->minLogR = minLogR;
	this->maxLogR = maxLogR;
	this->logRSteps = logRSteps;

	logRStepSize = ( maxLogR - minLogR ) / double( logRSteps - 1 );
}

void LogLogPlotCalculator::computeLogLogPlot( const Dataset & delayedTimeSeries, LogLogPlot & outLogLogPlot, bool printSteps )
{
	constexpr double UNDEFINED_CORRELATION_DIM_LOG = -1000.0;

	if( outLogLogPlot.getSize() > 0 )
		outLogLogPlot.clear();

	unsigned int examplesNum, examplesDim;

	double *linearizedDelayedTS = linearizeDelayedTS( delayedTimeSeries, examplesNum, examplesDim );

	int steps = 0;

	if( printSteps )
		std::cout << "Steps: ";

	for( double currLogR = minLogR; currLogR <= maxLogR; currLogR += logRStepSize ) {

		steps++;

		if( printSteps )
			std::cout << steps << " " << std::flush;

		double currR = exp( currLogR );

		double currCorrelationDim = computeCorrelationDimension( linearizedDelayedTS, examplesNum, examplesDim, currR );

		double currCorrelationDimLog = ( currCorrelationDim != 0.0 ) ? log( currCorrelationDim ) : UNDEFINED_CORRELATION_DIM_LOG;

		Point currLogLogPair( currLogR, currCorrelationDimLog );

		outLogLogPlot.appendPoint( currLogLogPair );
	}

	delete[] linearizedDelayedTS;
}

double * LogLogPlotCalculator::linearizeDelayedTS( const Dataset & delayedTimeSeries, unsigned int & examplesNum, unsigned int & examplesDim )
{
	examplesNum = delayedTimeSeries.getSize();
	examplesDim = delayedTimeSeries.getPatternsDimensionality() + 1;

	double *linearizedDelayedTS = new double[examplesNum*examplesDim];

	for( int currExampleIdx = 0; currExampleIdx < examplesNum; currExampleIdx++ ) {

		double currTarget;
		Pattern currPattern( delayedTimeSeries.getPatternsDimensionality() );

		delayedTimeSeries.getExampleAt( currExampleIdx, currTarget, currPattern );

		unsigned int currValueIdx;

		for( currValueIdx = 0; currValueIdx < currPattern.getDimensionality(); currValueIdx++ )
			*( linearizedDelayedTS + examplesDim * currExampleIdx + currValueIdx ) = currPattern.featureAt( currValueIdx );

		*( linearizedDelayedTS + examplesDim * currExampleIdx + currValueIdx ) = currTarget;
	}

	return linearizedDelayedTS;
}

double LogLogPlotCalculator::computeCorrelationDimension( const double * linearizedTS, unsigned int examplesNum, unsigned int examplesDim, double currR )
{
	double correlationDim = 0.0;

	for( unsigned int i = 0; i < examplesNum; i++ )
		for( unsigned int j = i + 1; j < examplesNum; j++ ) {

			double currExamplesDistance = 0.0;

			for( int currValueIdx = 0; currValueIdx < examplesDim; currValueIdx++ ) {

				double currValuesDiff = *( linearizedTS + examplesDim * i + currValueIdx ) - *( linearizedTS + examplesDim * j + currValueIdx );

				currExamplesDistance = currExamplesDistance + currValuesDiff * currValuesDiff;
			}

			currExamplesDistance = sqrt( currExamplesDistance );

			if( currExamplesDistance <= currR )
				correlationDim += 1.0;
		}

	correlationDim = correlationDim * 2.0 / ( examplesNum*( examplesNum - 1.0 ) );

	return correlationDim;
}
