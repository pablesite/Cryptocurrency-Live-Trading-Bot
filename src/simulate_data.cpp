#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>

#include "simulate_data.h"

using std::string;
using std::vector;

std::mutex SimulateData::_mutexSD;

/* Implementation of class "MessageQueue" */

template <typename T>
std::deque<T> MessageQueue<T>::receive(double &lookbackperiod)
{
    std::unique_lock<std::mutex> lck(_mtxMQ);

    _cdtMQ.wait(lck, [this, lookbackperiod]
                { return !(_queue.size()<lookbackperiod+1); });

    if (_queue.size() > lookbackperiod)
    {
        _queue.pop_front();
    }
    
    //std::cout << _queue.size() << std::endl;
    //std::cout << _queue.size() << std::endl;
    // return msg and remove from _queue
    //T msg = std::move(_queue.front());

    //_queue.pop_front(); // si lo comento, siempre obtendría el mismo dato... no se, pensar mejor

    return _queue;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // lock shared data
    std::lock_guard<std::mutex> lck(_mtxMQ);
    // before add a msg in the queue, clear it for having only last Traffic Light Phase in _queue
    // _queue.clear();
    // if (_queue.size() > 60)
    // {
    //     _queue.pop_front();
    // }
    // add a new message to the queue
    _queue.push_back(std::move(msg));

    // send a notification
    _cdtMQ.notify_one();
}

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
    double value;
    std::deque<double> data = _mqData->receive(lookbackperiod);

    // std::cout << data.size() << std::endl;
    for (int i=0; i < lookbackperiod; i++)
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
    double count=0;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); //Check: Max velocity is every 15 msecs aprox.
        x = x * (1 + (rand() % 2000 - 980) / 1000000.0);

        // store the last minute
        // std::lock_guard<std::mutex> lock(_mutexSD);
        // if (_data.size() > 60 ){
        //     _data.pop_front();
        // }
        //std::cout << "meto un dato a la cola: " << x << " " << count << std::endl;
        _mqData->send(std::move(x));
        count+= 1;
        // _data.emplace_back(std::move(x));
    }

    return;
}
