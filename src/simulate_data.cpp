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
    // Aquí debo ver cómo cojo todo el vector... en el receive de la cola no sería porque necesito los datos en la siguiente iteración
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    // std::cout << data.size() << std::endl;
    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
        // value += _mqData->receive();
    }

    return value / lookbackperiod;
}

void SimulateData::fetchData(double myCoinBase)
{
    //double data;
    // Connect with Binance
    //_bin.connect();

    // Fetch Data
    //_bin.fetch();

    std::cout << "Generating data " << std::endl;

    double x = myCoinBase;
    double count = 0;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); //Check: Max velocity is every 15 msecs aprox.
        x = x * (1 + (rand() % 2000 - 980) / 1000000.0);

        //std::cout << "meto un dato a la cola: " << x << " " << count << std::endl;
        _mqData->MessageQueue::send(std::move(x));

        count += 1;
        // _data.emplace_back(std::move(x));
    }

    return;
}
