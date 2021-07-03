/*
* COPYRIGHT NOTICE
*
* TimeSeriesFileWriter.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "ITimeSeriesFileWriter.h"

/**
Writes values from a time series in a sequential text file.
Values are separated by a newline.
*/
class TimeSeriesFileWriter : public ITimeSeriesFileWriter {

public :

	TimeSeriesFileWriter();

	void writeTimeSeries( const TimeSeries &timeSeries, const std::string &outFilePath ) override;
};
