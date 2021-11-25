#ifndef RETRIEVE_DATA_H
#define RETRIEVE_DATA_H

#include "message_queue.h"

/*
Abstract class for Fetch Data of Cryptoconcurrency
*/

class RetrieveData
{
public:
  RetrieveData();
  double retrieveDataFromQueue(double &lookbackperiod);

private:
  std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
