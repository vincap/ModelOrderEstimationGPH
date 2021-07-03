/*
* COPYRIGHT NOTICE
*
* GPHModelOrderEstimator.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "GPHModelOrderEstimator.h"
#include "../Dataset/Dataset.h"

GPHModelOrderEstimator::GPHModelOrderEstimator( unsigned int delay, double minLogR, double maxLogR, unsigned int logRSteps ) : llpCalculator( minLogR, maxLogR, logRSteps ), houghEstimator( DEFAULT_HOUGH_STEPS ) { this->delay = delay; }

GPHModelOrderEstimator::GPHModelOrderEstimator( unsigned int delay, double minLogR, double maxLogR, unsigned int logRSteps, unsigned int houghSteps ) : llpCalculator(minLogR, maxLogR, logRSteps), houghEstimator(houghSteps) { this->delay = delay; }

double GPHModelOrderEstimator::estimateModelOrder( const TimeSeries & timeSeries )
{
	Dataset delayedTS( delay, timeSeries );

	LogLogPlot llp;

	llpCalculator.computeLogLogPlot( delayedTS, llp, true );

	double attractorDimension = houghEstimator.estimateSlope( llp );

	return 2.0*attractorDimension;
}

