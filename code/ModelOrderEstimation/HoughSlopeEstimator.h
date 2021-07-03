/*
* COPYRIGHT NOTICE
*
* HoughSlopeEstimator.h -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#pragma once

#include "ILogLogPlotSlopeEstimator.h"

/**
	Class used to represent a line in polar coordinates.
*/
class PolarLine {

public :

	PolarLine(double r, double t) : rho(r), theta(t) {}

	inline double getRho() const { return rho; }

	inline double getTheta() const { return theta; }

private :

	double rho, theta;
};

/**
	The HoughSlopeEstimator class implements the ILogLogPlotSlopeEstimator interface, using the Hough transform for lines
	to compute the slope of the linear portion of a previously computed log-log plot and represented with a LogLogPlot object.
	Please note that, depending on the log(r) range, the log-log plot might contain several but irrelevant aligned points,
	which might be deceiving for the HoughSlopeEstimator. Hence, a manual cleanup of the plot might be needed in order to get
	the slope of the actual linear portion.
*/
class HoughSlopeEstimator : public ILogLogPlotSlopeEstimator {

public :

	HoughSlopeEstimator( unsigned int resolutionSteps );

	~HoughSlopeEstimator();

	double estimateSlope( const LogLogPlot &logLogPlot ) override;

	PolarLine getLatestLine() const;

private :

	void sampleRho( const LogLogPlot &logLogPlot );

	double computeMaxRho( const LogLogPlot &logLogPlot );

	int *voteProcedure( const LogLogPlot &logLogPlot );

	PolarLine findLineWithMostVotes( const int*votesAccumulator );

	const double MIN_THETA = 0.0, MAX_THETA = std::acos( -1.0 );

	unsigned int resolutionSteps;

	double thetaStepping, rhoStepping;

	double *sampledTheta, *sampledRho;

	unsigned int sampledThetaSize, sampledRhoSize;

	PolarLine latestLine;
};
