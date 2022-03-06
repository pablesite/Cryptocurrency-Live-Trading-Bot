#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <iomanip>
#include <deque>

#include "simulate_data.h"
#include "historic_data.h"
#include "binance.h"
#include "crypto_gui.h"


// forward declarations
class CryptoGuiPanel;
class CryptoGraphic;

enum class TypesOfData
{
    Binance,
    SimulateData,
    HistoricData
};

/*
Class for perform strategy of trading
*/

class Strategy : public std::enable_shared_from_this<Strategy>
{
public:
    // constructors
    Strategy(std::shared_ptr<Binance> data);
    Strategy(std::shared_ptr<SimulateData> data);
    Strategy(std::shared_ptr<HistoricData> data);

    // handlers
    void SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic);
    void SetCryptoGuiPanelHandle(std::shared_ptr<CryptoGuiPanel> cryptoGuiPanel);

    // getters
    double getData(double lookBackPeriod);
    double getBase();

    // main --> thread
    void cryptoBot();

private:
    // helpers functions
    double getIndex();
    void updateBase();

    // pointers for retrieve data
    std::shared_ptr<Binance> _dataBinance;
    std::shared_ptr<SimulateData> _dataSimulated;
    std::shared_ptr<HistoricData> _dataHistoric;

    // mutex
    // std::mutex _mtx;

    // auxiliary variable for select type of data
    TypesOfData _type;

    // config data of strategy
    std::string _exchange;
    std::string _cryptoConcurrency;
    std::string _strategy;
    double _investment;

    // data from binance //FOR THE FUTURE: to obtain through api of binance
    double _commission = 0.00075; // 0.075%

    // input data of strategy //FOR THE FUTURE: get from CryptoGuiPanel in Menu: "Configure Strategy"
    double _entry = 2 * _commission;
    double _bottomBreak = -1 * _commission;
    double _recession = -2 * _commission;
    double _topBreak = 1 * _commission;
    double _lookBackPeriod = 10;

    // output data of strategy
    double _value = 0;
    double _base = 0;
    double _openPosition;
};

#endif
