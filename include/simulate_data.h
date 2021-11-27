#ifndef SIMULATE_DATA_H
#define SIMULATE_DATA_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "fetch_data.h"
 #include "message_queue.h"
//#include "binance.h"



/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class SimulateData : public FetchData
{
public:
    SimulateData();
    void fetchData() override;
    double retrieveData(double &lookbackperiod) override;

protected:
    static std::mutex _mutexSD;

private:
    //Binance _bin;
    double _currentData;
    std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
