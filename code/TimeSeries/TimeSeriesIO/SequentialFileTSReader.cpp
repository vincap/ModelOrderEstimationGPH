/*
* COPYRIGHT NOTICE
*
* SequentialFileTSReader.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "SequentialFileTSReader.h"

#include <fstream>
#include <exception>

SequentialFileTSReader::SequentialFileTSReader() { }

void SequentialFileTSReader::readTimeSeries( const std::string &inFilePath, TimeSeries & outTimeSeries )
{
	std::ifstream inputFileReader( inFilePath );

	if( !inputFileReader.good() ) {

		inputFileReader.close();

		throw std::ios_base::failure( "An error occurred while opening file at " + inFilePath );
	}

	while( true ) {

		double val;

		inputFileReader >> val;

		if( inputFileReader.eof() )
			break;
		else if( inputFileReader.fail() ) {

			inputFileReader.close();

			outTimeSeries.clear();

			throw std::ios_base::failure( "An error occurred while reading from file at " + inFilePath );
		}

		outTimeSeries.appendValue( val );
	}

	inputFileReader.close();
}
