/*
* COPYRIGHT NOTICE
*
* TimeSeriesFileWriter.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "TimeSeriesFileWriter.h"

#include <fstream>

TimeSeriesFileWriter::TimeSeriesFileWriter() { }

void TimeSeriesFileWriter::writeTimeSeries( const TimeSeries & timeSeries, const std::string &outFilePath )
{
	std::ofstream outputFileWriter( outFilePath );

	if( !outputFileWriter.good() ) {

		outputFileWriter.close();

		throw std::ios_base::failure( "An error occurred while opening file at " + outFilePath );
	}

	for( unsigned int currValIdx = 0; currValIdx < timeSeries.getSize(); currValIdx++ ) {

		outputFileWriter << timeSeries.valueAt( currValIdx ) << std::endl;

		if( outputFileWriter.fail() ) {

			outputFileWriter.close();

			throw std::ios_base::failure( "An error occurred while writing time series on file at " + outFilePath );
		}
	}

	outputFileWriter.close();
}
