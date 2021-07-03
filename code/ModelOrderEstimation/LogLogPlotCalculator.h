/*
* COPYRIGHT NOTICE
*
* LogLogPlotCalculator.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "LogLogPlot.h"
#include "../Dataset/Dataset.h"

/**
	The LogLogPlotCalculator class implements the Grassberger-Procaccia algorithm to compute a discrete log-log plot
	for a given (delayed) time series. The slope of the linear portion of the curve is an approximation of the correlation
	dimension of the delayed time series.
	You can graphically plot the computed values and estimate the aforementioned slope by hand, or you can use the HoughSlopeEstimator
	provided in this package.
	Please note that depending on the log(r) range (i.e. [minLogR, maxLogR]), a manual cleanup of the plot might be necessary to
	remove irrelevant points which might negatively affect the HoughSlopeEstimator.
*/
class LogLogPlotCalculator {

public :

	LogLogPlotCalculator( double minLogR, double maxLogR, unsigned int logRSteps );

	void computeLogLogPlot(const Dataset& delayedTimeSeries, LogLogPlot &outLogLogPlot, bool printSteps = false );

private :

	double *linearizeDelayedTS( const Dataset& delayedTimeSeries, unsigned int &examplesNum, unsigned int &examplesDim );

	double computeCorrelationDimension( const double *linearizedTS, unsigned int examplesNum, unsigned int examplesDim, double currR );

	double minLogR, maxLogR, logRStepSize;

	unsigned int logRSteps;
};
