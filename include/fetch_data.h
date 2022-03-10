#ifndef FETCH_DATA_H
#define FETCH_DATA_H

/*
Abstract class for Fetch Data of differents types.
*/

class FetchData
{
public:
  // pure virtual functions
  virtual void fetchData() = 0;
  virtual double retrieveData(double &lookbackperiod) = 0;
};

#endif
