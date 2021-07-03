/*
* COPYRIGHT NOTICE
*
* ITimeSeriesFileReader.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "../TimeSeries.h"

#include <string>

/**
Interface to a generic time series file reader.
*/
class ITimeSeriesFileReader {

	virtual void readTimeSeries( const std::string &inFilePath, TimeSeries &outTimeSeries ) = 0;
};
