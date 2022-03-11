#ifndef HISTORIC_DATA_H
#define HISTORIC_DATA_H

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "fetch_data.h"
#include "message_queue.h"
#include "binance.h"



/*
Basic class for Historical Data
*/
class HistoricData : public FetchData
{
public:
    // constructor
    HistoricData();

    // fetch and from Historical Data and retrieve data from messageQueue
    double retrieveData(int &lookbackperiod);
    void fetchData() override;

    // create Historical Data
    void createHistoricData(std::shared_ptr<Binance> data);
    void closeFile(std::future<int>& fut);

    // helper function
    std::string OutputFormat(int unit_time);

private:
    // mq Data Shared Pointer
    std::shared_ptr<MessageQueue<double>> _mqData;
    bool _closeFile = false;
    std::mutex _mtx;
};

#endif
