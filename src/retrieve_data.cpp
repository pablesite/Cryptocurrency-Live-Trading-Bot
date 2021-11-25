#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <deque>

#include "retrieve_data.h"
#include "message_queue.h"

using std::string;
using std::vector;


RetrieveData::RetrieveData()
{
    _mqData = std::make_shared<MessageQueue<double>>();

    std::cout << "Constructor of FetchData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

double RetrieveData::retrieveDataFromQueue(double &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
    }

    return value / lookbackperiod;
}
