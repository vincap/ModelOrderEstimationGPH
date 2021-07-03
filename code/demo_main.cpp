/*
* COPYRIGHT NOTICE
*
* demo_main.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include <iostream>

#include "ModelOrderEstimation/GPHModelOrderEstimator.h"

#include "TimeSeries/TimeSeries.h"
#include "Dataset/Dataset.h"
#include "TimeSeries/TimeSeriesIO/SequentialFileTSReader.h"
#include "ModelOrderEstimation/LogLogPlotCalculator.h"
#include "ModelOrderEstimation/HoughSlopeEstimator.h"

int main( int argc, char** argv )
{
	const double MIN_LOG_R = -4.0, MAX_LOG_R = 0.0;
	const unsigned int LOG_R_STEPS = 50, HOUGH_RESOLUTION = 1000, DELAY = 20;

	// Handle to a time series file reader.
	SequentialFileTSReader timeSeriesReader;

	// TimeSeries object to store a time series.
	TimeSeries timeSeries;

	// Handle to a Grassberger-Procaccia llp calculator.
	LogLogPlotCalculator llpCalculator( MIN_LOG_R, MAX_LOG_R, LOG_R_STEPS );

	// LogLogPlot object to store a log-log plot.
	LogLogPlot computedLLP;

	// Handle to a HoughLines-based correlation dimension estimator.
	HoughSlopeEstimator corrDimEstimator( HOUGH_RESOLUTION );
	
	double attractorDim = .0;

	try {

		std::cout << "Reading time series from file... ";

		timeSeriesReader.readTimeSeries( "test_time_series.txt", timeSeries );

		std::cout << "Done!\nRead time series with " << timeSeries.getSize() << " values.\n";

		std::cout << "Building delayed time series with delay = " << DELAY << "... ";

		Dataset delayedTimeSeries( DELAY, timeSeries );

		std::cout << "Done!\nDelayed time series has " << delayedTimeSeries.getSize() << " samples of length " << delayedTimeSeries.getPatternsDimensionality() + 1 << std::endl;

		std::cout << "Computing log-log plot with the Grassberger-Procaccia algorithm " <<
			"(logR in [" << MIN_LOG_R << ", " << MAX_LOG_R << "] through " << LOG_R_STEPS << " steps)...\n";

		llpCalculator.computeLogLogPlot( delayedTimeSeries, computedLLP, true );

		std::cout << "Done!\nWriting log-log plot on file... ";

		LogLogPlot::writeLogLogPlot( "computed_llp.txt", computedLLP );

		std::cout << "Done!\nEstimating attractor dimension using Hough Transform for lines...";

		attractorDim = corrDimEstimator.estimateSlope( computedLLP );

	} catch( const std::exception& exc ) { std::cerr << exc.what(); return 1; }

	std::cout << "Done!\nAttractor dimension = " << attractorDim << "\nModel Order = " << 2.0 * attractorDim;

	return 0;	
}
