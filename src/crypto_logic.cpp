#include <iostream>
#include <future>

#include "crypto_logic.h"

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"


CryptoLogic::CryptoLogic()
{
    std::cout << "CryptoLogic constructor" << std::endl;

}

void CryptoLogic::startSimulation(){
    std::shared_ptr<SimulateData> dataSimulatedPtr = std::make_shared<SimulateData>();
    std::thread dataSimulated = std::thread(&SimulateData::fetchData, dataSimulatedPtr);

    // STRATEGY
    std::shared_ptr<Strategy> strategyDataSimulatedPtr = std::make_shared<Strategy>(dataSimulatedPtr);
    std::thread strategyDataSimulatedBot = std::thread(&Strategy::cryptoBot, strategyDataSimulatedPtr);

    dataSimulated.join();
    strategyDataSimulatedBot.join();

}

void CryptoLogic::setDataFromStrategy(double value){
    _actual_value = value;
}

void CryptoLogic::SetCryptoGraphicHandle(CryptoGraphic *cryptoGraphic) {
  _cryptoGraphic = cryptoGraphic;
}