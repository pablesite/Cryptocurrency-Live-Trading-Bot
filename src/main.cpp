#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"

int main()
{

    // Request what do you want to do?
    // 1 - Simulate the strategy
    //      1 - Simulated data
    //      2 - Historical data
    //      2 - Real time data
    // 2 - Create new data series

    int value;
    std::cout << "\nWelcome to the Cryptoconcurrency Live Trading Bot. Here you can either simulate a strategy or create new data series. \n";

    std::cout << "\nPlease, select between the following options: \n1: Simulate a strategy. \n2: Create new data series: \n";
    std::cout << "\nWhich one you prefer? : ";
    std::cin >> value;

    switch (value)
    {
    case 1:
    {
        std::cout << "\nPlease, select between the following options: \n1: Simulate with data simulated. \n2: Simulate with an historical data. \n3: Simulate with real time data. \n";
        std::cout << "\nWhich one you prefer? : ";
        std::cin >> value;
        switch (value)
        {
        case 1:
        {
            //DATA SIMULATED
            std::shared_ptr<SimulateData> dataSimulatedPtr = std::make_shared<SimulateData>();
            std::thread dataSimulated = std::thread(&SimulateData::fetchData, dataSimulatedPtr);

            // STRATEGY            
            std::shared_ptr<Strategy> strategyDataSimulatedPtr = std::make_shared<Strategy>(dataSimulatedPtr);
            std::thread strategyDataSimulatedBot = std::thread(&Strategy::cryptoBot, strategyDataSimulatedPtr);

            dataSimulated.join();
            strategyDataSimulatedBot.join();

            break;
        }
        case 2:
        {
            // HISTORICAL DATA (IN FILE)
            std::shared_ptr<HistoricData> historicDataPtr = std::make_shared<HistoricData>();
            std::thread historicData = std::thread(&HistoricData::fetchData, historicDataPtr);

            // STRATEGY
            std::shared_ptr<Strategy> strategyHistoricPtr = std::make_shared<Strategy>(historicDataPtr);
            std::thread strategyHistoricBot = std::thread(&Strategy::cryptoBot, strategyHistoricPtr);

            historicData.join();
            strategyHistoricBot.join();

            break;
        }
        case 3:
        {
            // REAL DATA IN REAL TIME
            std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
            std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

            // STRATEGY
            std::shared_ptr<Strategy> strategyBinancePtr = std::make_shared<Strategy>(binancePtr);
            std::thread strategyBinanceBot = std::thread(&Strategy::cryptoBot, strategyBinancePtr);

            binanceData.join();
            strategyBinanceBot.join();

            break;
        }
        default:
            std::cout << "\nSorry. Selected option is not valid. \n";
        }

        break;
    }

    case 2:
    {
        std::cout << "\nCreating new data series with real data: " << value << "\n";

        // REAL DATA IN REAL TIME
        std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
        std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);
        // 2. CREATE NEW DATA SERIES
        std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
        std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);

        writeHistoricData.join();
        binanceData.join();
        break;
    }

    default:
        std::cout << "\n Sorry. Selected option is not valid. \n";
    }

    return 0;
}