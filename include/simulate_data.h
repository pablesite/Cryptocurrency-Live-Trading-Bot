#ifndef SIMULATE_DATA_H
#define SIMULATE_DATA_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "fetch_data.h"
//#include "binance.h"

template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    std::deque<T> receive(double &lookbackperiod);

private:
    std::condition_variable _cdtMQ;
    std::mutex _mtxMQ;
    std::deque<T> _queue;
};

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class SimulateData : public FetchData
{
public:
    SimulateData();
    void fetchData(double myCoin) override;
    double retrieveData(double &lookbackperiod);

protected:
    static std::mutex _mutexSD;

private:
    //Binance _bin;
    double _currentData;
    std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
