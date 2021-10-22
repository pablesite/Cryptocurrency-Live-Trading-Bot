#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>

#include "fetch_data.h"


using std::string;
// using std::to_string;
using std::vector;

// pid and user doesn't change during the execution of system monitor.
// pid dosn't need invariant and can be initialed directly.
FetchData::FetchData() {
    // cpu_utilization_ = CpuUtilization();
    std::cout << "Constructor of FetchData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

void FetchData::fetchData() {
    //double data;
    // Connect with Binance
    //_bin.connect();

    // Fetch Data
    //_bin.fetch();
    std::cout << "Retrieving data " << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Retrieve Data: " << rand() % 2000 + 4000 << std::endl;
    }

    

    return;
}

