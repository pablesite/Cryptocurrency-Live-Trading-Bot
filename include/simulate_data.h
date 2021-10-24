#ifndef SIMULATE_DATA_H
#define SIMULATE_DATA_H

#include <string>
#include <vector>
#include <deque>

#include "fetch_data.h"
//#include "binance.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class SimulateData : public FetchData{
 public:
  SimulateData();
  void fetchData() override;

  std::deque<double> returnData() {return _data;};

 private:
    std::deque<double> _data;
    //Binance _bin;

};

#endif

