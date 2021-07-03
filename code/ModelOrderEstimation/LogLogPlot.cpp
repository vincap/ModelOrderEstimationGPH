/*
* COPYRIGHT NOTICE
*
* LogLogPlot.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "LogLogPlot.h"

#include <fstream>

void LogLogPlot::readLogLogPlot( const std::string & inFilePath, LogLogPlot & llp )
{
	std::ifstream inputFileReader( inFilePath );

	if( !inputFileReader.good() ) {

		inputFileReader.close();

		throw std::ios_base::failure("An error occurred while opening file at " + inFilePath);
	}

	if( llp.getSize() != 0 )
		llp.clear();

	while( true ) {

		double x, y;

		inputFileReader >> x;

		if( inputFileReader.eof() )
			break;
		else if( inputFileReader.fail() ) {

			llp.clear();

			inputFileReader.close();

			throw std::ios_base::failure( "An error occurred while reading log log plot from file at " + inFilePath );
		}

		inputFileReader >> y;

		if( inputFileReader.eof() ) {

			llp.clear();

			inputFileReader.close();

			throw std::ios_base::failure( "Unexpected format for log log plot file " + inFilePath );

		} else if( inputFileReader.fail() ) {

			llp.clear();

			inputFileReader.close();

			throw std::ios_base::failure( "An error occurred while reading log log plot from file at " + inFilePath );
		}

		Point newPoint( x, y );

		llp.appendPoint( newPoint );
	}

	inputFileReader.close();
}

void LogLogPlot::writeLogLogPlot( const std::string & outFilePath, const LogLogPlot & llp )
{
	std::ofstream outputFileWriter( outFilePath );

	if( !outputFileWriter.good() ) {

		outputFileWriter.close();

		throw std::ios_base::failure( "An error occurred while opening file at " + outFilePath );
	}

	for( unsigned int currPointIdx = 0; currPointIdx < llp.getSize(); currPointIdx++ ) {

		Point currPoint = llp.getPoint( currPointIdx );

		outputFileWriter << currPoint.getX() << " " << currPoint.getY() << std::endl;

		if( outputFileWriter.fail() ) {

			outputFileWriter.close();

			throw std::ios_base::failure( "An error occurred while writing log log plot on file at " + outFilePath );
		}
	}

	outputFileWriter.close();
}
