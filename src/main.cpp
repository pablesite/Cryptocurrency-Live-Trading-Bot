#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"


int main() {

    std::cout << "Main start!" << "\n";
    
    // Request what do you want to do? 
    // 1 - Simulate the strategy
    //      a - Historical data
    //      b - Real time data
    //      c - Simulated data 
    // 2 - Create new data series

   

    // 1. SIMULATE THE STRATEGY
    
    // HISTORICAL DATA (IN FILE)
    //std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
    //std::thread readHistoricData = std::thread(&HistoricData::fetchData, dataFilePtr);

    // REAL DATA IN REAL TIME
    std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
    std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

    // DATA SIMULATED
    //std::shared_ptr<SimulateData> data = std::make_shared<SimulateData>();
    // std::thread fetchData = std::thread(&SimulateData::fetchData, data, myCoinBase);

    
    // STRATEGY
    //std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
    //std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, binancePtr);


    // 2. CREATE NEW DATA SERIES
    std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
    std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);





    //readHistoricData.join();
    writeHistoricData.join();
    binanceData.join();
    // cryptoBot.join();

    return 0;
}