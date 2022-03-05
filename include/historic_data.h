#ifndef HISTORIC_DATA_H
#define HISTORIC_DATA_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "fetch_data.h"
#include "message_queue.h"
#include "binance.h"


namespace locations {

/***** PATHS *****/
// const std::string kProcDirectory{"/proc/"};
// const std::string kOSPath{"/etc/os-release"};


}
/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class HistoricData : public FetchData
{
public:
    HistoricData();
    void fetchData() override;
    double retrieveData(double &lookbackperiod);
    void unblockThread();
    std::string OutputFormat(int unit_time);
    void createHistoricData(std::shared_ptr<Binance> data);

protected:
    static std::mutex _mutexSD;

private:
    //Binance _bin;
    double _currentData;
    std::shared_ptr<MessageQueue<double>> _mqData;
};

#endif
