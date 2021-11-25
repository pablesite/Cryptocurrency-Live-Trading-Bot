#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"
#include "retrieve_data.h"

int main()
{

    // Request what do you want to do?
    // 1 - Simulate the strategy
    //      1 - Historical data
    //      2 - Real time data
    //      3 - Simulated data
    // 2 - Create new data series

    // std::vector<std::pair<std::string, float>> coords {{"start_x", 0}, {"start_y", 0}, {"end_x", 0}, {"end_y", 0}};
    // for (auto &i : coords) {
    //     while(!InsertInputValue(i.first, i.second)){}
    // }

    int value;
    std::cout << "Welcome to the Cryptoconcurrency Live Trading Bot. Here you can either simulate a strategy (1), or create new data series (2). \n";

    std::cout << "Please, enter 1 to simulate a strategy or 2 to create new data series: ";
    std::cin >> value;

    switch (value)
    {
    case 1:
    {
        std::cout << "\n Please, select between the following options: \n 1: Simulate with an historical data. \n 2: Simulate with real time data. \n 3: Simulate with data simulated. \n";
        std::cout << "Which one you prefer? : ";
        std::cin >> value;
        switch (value)
        {
        case 1:
        {
            std::cout << "value: " << value;
            // HISTORICAL DATA (IN FILE)
            std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
            std::thread readHistoricData = std::thread(&HistoricData::fetchData, dataFilePtr);

            // STRATEGY
            // std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
            // std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, binancePtr);

            readHistoricData.join();
            // cryptoBot.join();

            break;
        }
        case 2:
        {
            std::cout << "value: " << value;
            // REAL DATA IN REAL TIME
            std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
            std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

            // STRATEGY
            // std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
            // std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, binancePtr);

            binanceData.join();
            //cryptoBot.join();

            break;
        }
        case 3:
        {
            std::cout << "value: " << value;
            //DATA SIMULATED
            std::shared_ptr<SimulateData> data = std::make_shared<SimulateData>();
            std::thread fetchData = std::thread(&SimulateData::fetchData, data);

            // STRATEGY

            //REVISAR ESTO. HE HECHO UNA CLASE RETRIEVEDATA PARA OBTENER DATOS DE LA COLA DE MENSAJES PERO YO NO SE SI ESTO ESTÁ TOMANDO DATOS DE VERDAD... REPENSAR MEJOR.
            
            std::shared_ptr<Strategy> crypto = std::make_shared<Strategy>();
            std::shared_ptr<RetrieveData> retrieveData = std::make_shared<RetrieveData>();
            std::thread cryptoBot = std::thread(&Strategy::cryptoBot, crypto, retrieveData);

            fetchData.join();
            cryptoBot.join();

            break;
        }
        default:
            std::cout << "\n Sorry. Selected option is not valid. \n";
        }

        break;
    }

    case 2:
    {
        std::cout << "\n Creating new data series with real data: " << value << "\n";

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