#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"


int main() {

    std::cout << "Main start!" << "\n";
    double myCoinBase = 50000;
    

    //std::shared_ptr<SimulateData> data = std::make_shared<SimulateData>();
    std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
    std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
  
    // std::thread fetchData = std::thread(&SimulateData::fetchData, data, myCoinBase);
    std::thread binanceData = std::thread(&Binance::fetchData, binancePtr, myCoinBase);
    std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, binancePtr);

    binanceData.join();
    // cryptoBot.join();

    return 0;
}