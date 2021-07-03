/*
* COPYRIGHT NOTICE
*
* SequentialFileTSReader.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include <string>

#include "ITimeSeriesFileReader.h"

/**
Reads a time series from a text file in which time series' values are separated by a newline.
*/
class SequentialFileTSReader : public ITimeSeriesFileReader {

public :

	SequentialFileTSReader();

	void readTimeSeries( const std::string &inFilePath, TimeSeries &outTimeSeries ) override;
};
