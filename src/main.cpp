#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"


int main() {

    std::cout << "Main start!" << "\n";
    
    
    // DATA SIMULATED
    //std::shared_ptr<SimulateData> data = std::make_shared<SimulateData>();
    // std::thread fetchData = std::thread(&SimulateData::fetchData, data, myCoinBase);

    // REAL DATA IN REAL TIME
    std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
    std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

    // REAL DATA STORED IN FILE
    std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
    //std::thread readHistoricData = std::thread(&HistoricData::fetchData, dataFilePtr);

    std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);
    
    // STRATEGY
    //std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
    //std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, binancePtr);

    //readHistoricData.join();
    writeHistoricData.join();
    binanceData.join();
    // cryptoBot.join();

    return 0;
}