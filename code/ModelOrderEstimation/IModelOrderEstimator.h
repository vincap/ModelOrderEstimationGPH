/*
* COPYRIGHT NOTICE
*
* IModelOrderEstimator.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "../TimeSeries/TimeSeries.h"

class IModelOrderEstimator {

public :

	virtual double estimateModelOrder(const TimeSeries &timeSeries) = 0;
};
