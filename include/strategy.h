#ifndef STRATEGY_H
#define STRATEGY_H

//#include <string>
//#include <deque>
// #include <vector>
#include "simulate_data.h"
#include "binance.h"
#include "historic_data.h"
#include "message_queue.h"
#include "crypto_logic.h"

#include "crypto_gui.h"

// forward declarations
class CryptoGuiPanel;
class CryptoLogic;
class CryptoGraphic;

/*
Basic class for Fetch Data of Cryptoconcurrency
*/

enum class TypesOfData
{
    Binance,
    SimulateData,
    HistoricData
};

class Strategy
{
public:
    Strategy(std::shared_ptr<Binance> data);
    Strategy(std::shared_ptr<SimulateData> data);
    Strategy(std::shared_ptr<HistoricData> data);
    void SetCryptoLogicHandle(std::shared_ptr<CryptoLogic> cryptoLogic);
    //void SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic);
    void SetCryptoGraphicHandle(CryptoGraphic * cryptoGraphic);
    void SetCryptoGuiPanelHandle(CryptoGuiPanel * cryptoGuiPanel);
    
    double getData(double lookbackperiod);
    void cryptoBot();

    double getBase();

private:
    std::shared_ptr<Binance> data_binance;
    std::shared_ptr<SimulateData> data_simulated;
    std::shared_ptr<HistoricData> data_historic;

    TypesOfData _type;
    //graphicsPanel...
    std::shared_ptr<CryptoLogic> _cryptoLogic;
    CryptoGraphic * _cryptoGraphic;
    CryptoGuiPanel * _cryptoGuiPanel;


    double _base=0;
    
};

#endif
