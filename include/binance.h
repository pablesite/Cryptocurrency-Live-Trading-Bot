#ifndef BINANCE_H
#define BINANCE_H

#include <string>
#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <curl/curl.h>

#include "fetch_data.h"
#include "message_queue.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class Binance : public FetchData
{
public:
    Binance();
    void fetchData() override;
    double retrieveData(double &lookbackperiod) override;
    void configureAPI(const char * URL);

protected:
private:
    //Binance _bin;
    double _currentData;
    std::shared_ptr<MessageQueue<double>> _mqData;
    CURL *_curl;
    CURLcode _res;
    std::string _readBuffer;
};

#endif
