#include <iostream>
#include <future>

#include "simulate_data.h"
#include "strategy.h"


int main() {
    std::cout << "Main start!" << "\n";
    double myCoin = 50000;

    std::shared_ptr<SimulateData> data = std::make_shared<SimulateData>();
    std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
  
    std::thread fetchData = std::thread(&SimulateData::fetchData, data, myCoin);
    std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, data, myCoin);

    fetchData.join();
    cryptoBot.join();

    return 0;
}