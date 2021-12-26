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
    // std::shared_ptr<SimulateData> dataSimulatedPtr = std::make_shared<SimulateData>();
    // std::thread dataSimulated = std::thread(&SimulateData::fetchData, dataSimulatedPtr);

    // // STRATEGY
    // std::shared_ptr<Strategy> strategyDataSimulatedPtr = std::make_shared<Strategy>(dataSimulatedPtr);
    // std::thread strategyDataSimulatedBot = std::thread(&Strategy::cryptoBot, strategyDataSimulatedPtr);

    // dataSimulated.join();
    // strategyDataSimulatedBot.join();
    std::cout << "Paso por startSimulation?" << std::endl;

    _cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::paintEvent)); 
    _cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint)); //Esto sobreescribe el asunto. Estamos jodidos. Además, no es necesario porque se puede usar la de la clase CryptoGui
    //_cryptoGraphic->paintNow();

}

void CryptoLogic::setDataFromStrategy(double value){
    _actual_value = value;
}

void CryptoLogic::SetCryptoGraphicHandle(CryptoGraphic *cryptoGraphic) {
  _cryptoGraphic = cryptoGraphic;

}