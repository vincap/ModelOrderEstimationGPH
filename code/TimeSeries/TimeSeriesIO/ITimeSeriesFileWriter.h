/*
* COPYRIGHT NOTICE
*
* ITimeSeriesFileWriter.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include <string>

#include "../TimeSeries.h"

/**
Interface to a generic time series file writer.
*/
class ITimeSeriesFileWriter {

public:

	virtual void writeTimeSeries( const TimeSeries &timeSeries, const std::string &outFilePath ) = 0;
};
