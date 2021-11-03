#ifndef SIMULATE_DATA_H
#define SIMULATE_DATA_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>

#include "fetch_data.h"
//#include "binance.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class SimulateData : public FetchData
{
public:
    SimulateData();
    void fetchData(double myCoin) override;

    std::deque<double> returnData() { return _data; }; //Sería mejor un waitForData que hiciera un receive de una cola de mensajes...

protected:
    static std::mutex _mutexSD;

private:
    std::deque<double> _data;
    //Binance _bin;
};

#endif
