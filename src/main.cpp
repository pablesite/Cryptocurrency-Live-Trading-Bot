#include <iostream>
#include <future>

#include "simulate_data.h"
#include "strategy.h"


int main() {
    std::cout << "Main start!" << "\n";

    SimulateData* data = new SimulateData();
    Strategy* crypto = new Strategy();

    std::thread fetchData =std::thread(&SimulateData::fetchData, data);

    std::deque<double> data_returned = data->returnData();
    std::thread cryptoBot =std::thread(&Strategy::cryptoBot, crypto, data_returned);

    fetchData.join();
    cryptoBot.join();

    return 0;
}