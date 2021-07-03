/*
* COPYRIGHT NOTICE
*
* HoughSlopeEstimator.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "HoughSlopeEstimator.h"

HoughSlopeEstimator::HoughSlopeEstimator( unsigned int resolutionSteps ) : latestLine(-1.0, -1.0)
{
	this->resolutionSteps = resolutionSteps;

	thetaStepping = ( MAX_THETA - MIN_THETA ) / double( resolutionSteps );

	sampledThetaSize = resolutionSteps + 1;

	sampledTheta = new double[sampledThetaSize];

	for( unsigned int i = 0; i < sampledThetaSize; i++ )
		*( sampledTheta + i ) = MIN_THETA + i * thetaStepping;

	rhoStepping = 0.0;
	sampledRhoSize = 0;
	sampledRho = nullptr;
}

HoughSlopeEstimator::~HoughSlopeEstimator()
{
	delete[] sampledTheta;

	if( sampledRho != nullptr )
		delete[] sampledRho;
}

double HoughSlopeEstimator::estimateSlope( const LogLogPlot & logLogPlot )
{
	sampleRho( logLogPlot );

	int *votesAccumulator = voteProcedure( logLogPlot );

	PolarLine mostVotedLine = findLineWithMostVotes( votesAccumulator );

	latestLine = mostVotedLine;

	double slope = std::cos( mostVotedLine.getTheta() ) / std::sin( mostVotedLine.getTheta() ) * -1.0;

	delete[] votesAccumulator;
	delete[] sampledRho;

	rhoStepping = 0;
	sampledRhoSize = 0;
	sampledRho = nullptr;

	return slope;
}

PolarLine HoughSlopeEstimator::getLatestLine() const
{
	return latestLine;
}

void HoughSlopeEstimator::sampleRho( const LogLogPlot & logLogPlot )
{
	double maxRho = computeMaxRho( logLogPlot );

	rhoStepping = 2.0 * maxRho / double( resolutionSteps );

	sampledRhoSize = resolutionSteps + 1;

	sampledRho = new double[sampledRhoSize];

	for( unsigned int i = 0; i < sampledRhoSize; i++ )
		*( sampledRho + i ) = -maxRho + i * rhoStepping;
}

double HoughSlopeEstimator::computeMaxRho( const LogLogPlot & logLogPlot )
{
	double maxRho = std::numeric_limits<double>::min();

	for( unsigned int currPointIdx = 0; currPointIdx < logLogPlot.getSize(); currPointIdx++ ) {

		double distance = logLogPlot.getPoint( currPointIdx ).norm2();

		if( distance > maxRho )
			maxRho = distance;
	}

	return maxRho;
}

int * HoughSlopeEstimator::voteProcedure( const LogLogPlot & logLogPlot )
{
	int *votesAccumulator = new int[sampledThetaSize*sampledRhoSize];

	for( unsigned int i = 0; i < sampledThetaSize; i++ )
		for( unsigned int j = 0; j < sampledRhoSize; j++ )
			*( votesAccumulator + sampledRhoSize * i + j ) = 0;

	for( unsigned int currPointIdx = 0; currPointIdx < logLogPlot.getSize(); currPointIdx++ ) {

		Point currPoint = logLogPlot.getPoint( currPointIdx );

		for( unsigned int currThetaIdx = 0; currThetaIdx < sampledThetaSize; currThetaIdx++ ) {

			double currTheta = *( sampledTheta + currThetaIdx );

			double currRho = currPoint.getX()*std::cos( currTheta ) + currPoint.getY()*std::sin( currTheta );

			int closestRhoIdx = int( std::round( currRho / rhoStepping + double( resolutionSteps ) / 2.0 ) );

			*( votesAccumulator + sampledRhoSize * currThetaIdx + closestRhoIdx ) += 1;
		}
	}

	return votesAccumulator;
}

PolarLine HoughSlopeEstimator::findLineWithMostVotes( const int * votesAccumulator )
{
	int maxVotes = -1;

	double maxTheta, maxRho;

	for( unsigned int thetaIdx = 0; thetaIdx < sampledThetaSize; thetaIdx++ )
		for( unsigned int rhoIdx = 0; rhoIdx < sampledRhoSize; rhoIdx++ )
			if( *( votesAccumulator + sampledRhoSize * thetaIdx + rhoIdx ) > maxVotes ) {

				maxVotes = *( votesAccumulator + sampledRhoSize * thetaIdx + rhoIdx );

				maxTheta = *( sampledTheta + thetaIdx );
				maxRho = *( sampledRho + rhoIdx );
			}

	PolarLine outputLine( maxRho, maxTheta );
	return outputLine;
}
