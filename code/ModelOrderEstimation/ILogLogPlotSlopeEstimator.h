/*
* COPYRIGHT NOTICE
*
* ILogLogPlotSlopeEstimator.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "LogLogPlot.h"

class ILogLogPlotSlopeEstimator {

public :

	virtual double estimateSlope( const LogLogPlot &logLogPlot ) = 0;
};