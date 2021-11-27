#ifndef FETCH_DATA_H
#define FETCH_DATA_H

#include <deque>

/*
Abstract class for Fetch Data of Cryptoconcurrency
*/

class FetchData
{
public:
  virtual void fetchData() = 0;
  virtual double retrieveData(double &lookbackperiod) = 0;

};

#endif
