/*
* COPYRIGHT NOTICE
*
* GPHModelOrderEstimator.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "IModelOrderEstimator.h"
#include "LogLogPlotCalculator.h"
#include "HoughSlopeEstimator.h"

/**
	The GPHModelOrderEstimator is just a facade to the Grassberger-Procaccia + HoughLines approach to
	model order estimation. Internally, it creates a LogLogPlotCalculator object and a HoughSlopeEstimator object
	which are used to estimate the model order of a given time series. It automatically computes the log-log plot
	using the LogLogPlotCalculator instance, and feeds the resulting LogLogPlot object to the HoughSlopeEstimator
	instance to estimate the correlation dimension. Its estimateModelOrder(timeSeries) method returns the model order
	for the given time series, which is twice the correlation dimension returned by the HoughSlopeEstimator.
	Please note that to get a good estimate of the correlation dimension by the HoughSlopeEstimator, a manual cleanup
	of the plot might be needed (see HoughSlopeEstimator.h). Unless it is safe to assume that no irrelevant points
	are present in the plot and that no cleanup is necessary, please, do not use this class and explicitly use
	the standalone LogLogPlotCalculator and HoughSlopeEstimator.
*/
class GPHModelOrderEstimator : public IModelOrderEstimator {

public :

	GPHModelOrderEstimator( unsigned int delay, double minLogR, double maxLogR, unsigned int logRSteps );

	GPHModelOrderEstimator( unsigned int delay, double minLogR, double maxLogR, unsigned int logRSteps, unsigned int houghSteps );

	double estimateModelOrder( const TimeSeries &timeSeries ) override;

private :

	const unsigned int DEFAULT_HOUGH_STEPS = 10000;

	unsigned int delay;

	LogLogPlotCalculator llpCalculator;
	HoughSlopeEstimator houghEstimator;
};
