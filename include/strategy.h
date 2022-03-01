#ifndef STRATEGY_H
#define STRATEGY_H

//#include <string>
//#include <deque>
// #include <vector>
#include "simulate_data.h"
#include "binance.h"
#include "historic_data.h"
#include "message_queue.h"

#include "crypto_gui.h"

// forward declarations
class CryptoGuiPanel;
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

class Strategy : public std::enable_shared_from_this<Strategy> 
{
public:
    Strategy(std::shared_ptr<Binance> data);
    Strategy(std::shared_ptr<SimulateData> data);
    Strategy(std::shared_ptr<HistoricData> data);
    //void SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic);
    void SetCryptoGraphicHandle(CryptoGraphic * cryptoGraphic);
    void SetCryptoGuiPanelHandle(CryptoGuiPanel *cryptoGuiPanel);
    
    double getData(double lookbackperiod);
    void cryptoBot();

    double getBase();

private:

    double getIndex();
    void updateBase();

    std::shared_ptr<Binance> data_binance;
    std::shared_ptr<SimulateData> data_simulated;
    std::shared_ptr<HistoricData> data_historic;

    TypesOfData _type;
    //graphicsPanel...

    // CryptoGraphic * _cryptoGraphic;
    //std::shared_ptr<CryptoGuiPanel> _cryptoGuiPanel;
     CryptoGuiPanel * _cryptoGuiPanel;

    double _value = 0;
    double _base = 0;
    
};

#endif
