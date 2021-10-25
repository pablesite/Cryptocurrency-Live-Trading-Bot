#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>


#include "simulate_data.h"

using std::string;
using std::vector;

std::mutex SimulateData::_mutexSD;

SimulateData::SimulateData() {

    std::cout << "Constructor of FetchData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

void SimulateData::fetchData(double myCoin) {
    //double data;
    // Connect with Binance
    //_bin.connect();

    // Fetch Data
    //_bin.fetch();

    std::cout << "Retrieving data " << std::endl;

    double x = myCoin;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        x = x * ( 1 + (rand() % 2000 - 1000)/1000000.0);        
        
        std::cout << "Retrieve Data: " << x << std::endl;

        // store the last minute
        std::lock_guard<std::mutex> lock(_mutexSD);
        if (_data.size() > 60 ){
            _data.pop_front();
        }
        _data.emplace_back(std::move(x));
        
    }

    return;
}

