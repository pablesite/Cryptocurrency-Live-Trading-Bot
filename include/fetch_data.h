#ifndef FETCH_DATA_H
#define FETCH_DATA_H

/*
Abstract class for Fetch Data of Cryptoconcurrency
*/

class FetchData {
 public:
  virtual void fetchData(double myCoin) = 0;

};

#endif

