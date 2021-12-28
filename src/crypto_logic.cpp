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


    std::cout << "Paso por startSimulation 1" << std::endl;
    // _cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));
    std::shared_ptr<SimulateData> dataSimulatedPtr = std::make_shared<SimulateData>();
    std::thread dataSimulated = std::thread(&SimulateData::fetchData, dataSimulatedPtr);

    // // STRATEGY
    // std::cout << "Paso por startSimulation 1.5" << std::endl;
    // std::shared_ptr<Strategy> strategyDataSimulatedPtr = std::make_shared<Strategy>(dataSimulatedPtr);
    // std::cout << "Paso por startSimulation 1.7" << std::endl;
    // //std::shared_ptr<CryptoLogic> cryptoLogic1 = std::make_shared<CryptoLogic>();

    // //strategyDataSimulatedPtr->SetCryptoLogicHandle(shared_from_this());
    // std::cout << "Graphics in Logic is: " << _cryptoGraphic;
    // // strategyDataSimulatedPtr->SetCryptoGraphicHandle(_cryptoGraphic);

    // std::thread strategyDataSimulatedBot = std::thread(&Strategy::cryptoBot, strategyDataSimulatedPtr); //PROBLEMAS CON EL PUNTERO
    // std::cout << "Paso por startSimulation 1.9" << std::endl;
    

    dataSimulated.join();
    // strategyDataSimulatedBot.join();
    std::cout << "Paso por startSimulation 2" << std::endl;


    

}

void CryptoLogic::setDataFromStrategy(double value){
    _actual_value = value;
}

void CryptoLogic::SetCryptoGraphicHandle(CryptoGraphic * cryptoGraphic) {
  _cryptoGraphic = cryptoGraphic;

}

void CryptoLogic::sendToLogic(double value)
{
    std::cout << "data is: " << value << std::endl;
    _cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::paintEvent)); 
    //_cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint)); //Esto sobreescribe el asunto. 
    //Estamos jodidos. Además, no es necesario porque se puede usar la de la clase CryptoGui
}