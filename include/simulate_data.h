#ifndef SIMULATE_DATA_H
#define SIMULATE_DATA_H


#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>
#include "fetch_data.h"
#include "message_queue.h"

/*
Basic class for Fetch Data of Data Simulated
*/
class SimulateData : public FetchData
{
public:
    // constructor
    SimulateData();

    // fetch and from data simulated and retrieve data from messageQueue 
    void fetchData() override;
    double retrieveData(double &lookbackperiod) override;

private:
    std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
