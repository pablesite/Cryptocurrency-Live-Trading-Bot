#ifndef BINANCE_H
#define BINANCE_H

#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <curl/curl.h>
#include <json/json.h>
#include <future>

#include "fetch_data.h"
#include "message_queue.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
*/
class Binance : public FetchData
{
public:
    // constructor
    Binance();
    
    // fetch and from Binance and retrieve data from messageQueue 
    void fetchData() override;
    double retrieveData(int &lookbackperiod) override;

    // propietary function
    void configureAPI(const char * URL);

private:
    // mq Data Shared Pointer
    std::shared_ptr<MessageQueue<double>> _mqData;
    
    // API variables
    CURL *_curl;
    CURLcode _res;
    std::string _readBuffer;
};

#endif
