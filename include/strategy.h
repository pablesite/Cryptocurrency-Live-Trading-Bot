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
    double getData(double lookbackperiod);
    void cryptoBot();

private:
    std::shared_ptr<Binance> data_binance;
    std::shared_ptr<SimulateData> data_simulated;
    std::shared_ptr<HistoricData> data_historic;

    TypesOfData _type;
    //graphicsPanel...
    std::shared_ptr<CryptoLogic> _cryptologic;
};

#endif
