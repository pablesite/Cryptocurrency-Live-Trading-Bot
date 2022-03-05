#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <deque>

#include "simulate_data.h"
#include "message_queue.h"

using std::string;
using std::vector;

std::mutex SimulateData::_mutexSD;

SimulateData::SimulateData()
{
    _mqData = std::make_shared<MessageQueue<double>>();

    std::cout << "Constructor of FetchData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

double SimulateData::retrieveData(double &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
    }

    return value / lookbackperiod;
}

void SimulateData::fetchData()
{
    // double data;
    //  Connect with Binance
    //_bin.connect();

    // Fetch Data
    //_bin.fetch();


    std::cout << "Generating simulated data " << std::endl;

    double myCoinBase = 50000;
    double x = myCoinBase;
    double count = 0;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Check: Max velocity is every 15 msecs aprox.
        x = x * (1 + (rand() % 2000 - 990) / 10000000.0);

        // std::cout << "meto un dato a la cola: " << x << " " << count << std::endl; //DEBUG
        _mqData->MessageQueue::send(std::move(x));

        count += 1;
        // _data.emplace_back(std::move(x));
    }

    return;
}

void SimulateData::unblockThread()
{
    std::cout << "\n\nTEST UNBLOCK THREAD";
     _mqData->MessageQueue::unblockThread();

    // _mqData->MessageQueue::send(std::move(0));
    // _mqData->MessageQueue::send(std::move(0));
    // _mqData->MessageQueue::unblockThread();
    // _mqData->MessageQueue::unblockThread();
}