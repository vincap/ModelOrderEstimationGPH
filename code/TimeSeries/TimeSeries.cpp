/*
* COPYRIGHT NOTICE
*
* TimeSeries.cpp -- (c) 2020 Vincenzo Capone, University of Naples Parthenope.
*/

#include "TimeSeries.h"

TimeSeries::TimeSeries() {}

void TimeSeries::appendValue( double value ) { baseContainer.push_back( value ); }

double & TimeSeries::valueAt( unsigned int index ) { return baseContainer.at( index ); }

const double & TimeSeries::valueAt( unsigned int index ) const { return baseContainer.at( index ); }

unsigned int TimeSeries::getSize() const { return baseContainer.size(); }

void TimeSeries::clear() { baseContainer.clear(); }

TimeSeries::~TimeSeries() { }
