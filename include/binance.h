#ifndef BINANCE_H
#define BINANCE_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "fetch_data.h"
#include "message_queue.h"


/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class Binance : public FetchData
{
public:
    Binance();
    void fetchData(double myCoin) override;
    double retrieveData(double &lookbackperiod);

protected:
 
private:
    //Binance _bin;
    double _currentData;
    std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
