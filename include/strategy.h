#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <deque>
// #include <vector>
#include "simulate_data.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class Strategy {
 public:
  Strategy();
  void cryptoBot(std::shared_ptr<SimulateData> data, double myCoin);


 private:


};

#endif

