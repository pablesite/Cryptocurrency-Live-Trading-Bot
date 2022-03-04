#include <string>
#include <vector>
#include <iostream>
// #include <chrono>
// #include <future>
#include <deque>

#include "strategy.h"
#include "simulate_data.h"
#include "binance.h"
#include "message_queue.h"
#include <iomanip>

using std::string;
using std::vector;

Strategy::Strategy(std::shared_ptr<Binance> data) : data_binance(move(data))
{
    std::cout << "Constructor of Strategy with real data from Binance " << std::endl;

    _type = TypesOfData::Binance;
}

Strategy::Strategy(std::shared_ptr<SimulateData> data) : data_simulated(move(data))
{
    std::cout << "Constructor of Strategy with data simulated " << std::endl;
    _type = TypesOfData::SimulateData;
}

Strategy::Strategy(std::shared_ptr<HistoricData> data) : data_historic(move(data))
{
    std::cout << "Constructor of Strategy with historic data " << std::endl;
    _type = TypesOfData::HistoricData;
}

double Strategy::getData(double lookbackperiod)
{
    switch (_type)
    {
    case TypesOfData::Binance:
    {
        return data_binance->retrieveData(lookbackperiod);
        break;
    }
    case TypesOfData::SimulateData:
    {
        return data_simulated->retrieveData(lookbackperiod);
        break;
    }
    case TypesOfData::HistoricData:
    {
        return data_historic->retrieveData(lookbackperiod);
        break;
    }
    default:
    {
        std::cout << "Error: There is no type selected." << std::endl;
        return 0;
        break;
    }
    }
}

double Strategy::getBase()
{
    return _base;
}

double Strategy::getIndex()
{
    return _value / _base - 1;
}

void Strategy::updateBase()
{
    // update base value
    _base = _value;

    // update limits in cryptoGraphic
    _cryptoGraphic->setLimits(_open_position, _entry, _bottom_break, _recession, _top_break);
}

void Strategy::setInvestment(double investment)
{
    _investment = investment;
}

void Strategy::cryptoBot()
{

    std::cout << "CryptoBot working " << std::endl;

    // set strategy handle
    _cryptoGuiPanel->setStrategyHandle(shared_from_this());
    _cryptoGraphic->setStrategyHandle(shared_from_this());

    // get config data
    _exchange = _cryptoGuiPanel->getExchange();
    _cryptoConcurrency = _cryptoGuiPanel->getCryptoConcurrency();
    _strategy = _cryptoGuiPanel->getStrategy();
    _investment = _cryptoGuiPanel->getInvestment();

    // output strategy data
    // _open_position = false;     // to send
    double investment_acc = 0;  // to send
    double order = 0;           // to send
    double benefit = 0;         // to send
    double benefits_acc = 0;    // to send
    double computedData = 0;
    double nOrders = 0;         // to send

    // set base value
    _base = getData(_lookbackperiod);
    std::cout << "data generated: " << _base << std::endl;  //DEBUG

    // set CryptoGraphic
    // _cryptoGraphic->setStrategyData(_commission, _entry, _top_break, _recession); // TO REVIEW
    // _cryptoGraphic->setLimits();
    //_cryptoGraphic->setLimits(_open_position, _entry, _bottom_break, _recession, _top_break);
    updateBase();
    

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Para que las simulaciones vayan a tiempo real (1000). ¿no debería limitar el tiempo sólo en la obtención de datos?
        // Además, si paro el hilo de ejecución (botón stop) cuando no está esperando, peta el hilo y da error de core dump o cosas similares.
        //  Puede que esto tenga que ver por qué da error más veces lo de los datos reales. Pensar bien esto!!!

        // retrieve data
        _value = getData(_lookbackperiod);
        _cryptoGraphic->setActualValue(_value);

        computedData += 1;

        if (_open_position == false)
        {
            std::cout << std::setprecision(4) << std::fixed << "To buy " << _value << " => " << (1 + _bottom_break) * _base << " < " << _base << " > " << (1 + _entry) * _base << std::endl;
            // to update base if the trend is negative
            if (getIndex() < _bottom_break)
            {
                // updateBase
                std::cout << "Update the base: Descending " << _value << " " << std::endl;
                updateBase();
            }

            // to make an order
            if (getIndex() > _entry)
            {
                // perform an order
                order = _investment / (_value * (1 + _commission));
                investment_acc += _investment;
                // order = invest_qty * _value * (1 + _commission); // simulate the bought

                // manage position
                _open_position = true;
                nOrders += 1;

                // updateBase
                std::cout << "\nBuying my position " << order << " bitcoint. Actual value: " << _value << "." << std::endl;
                updateBase();
            }
        }
        else
        {
            std::cout << std::setprecision(4) << std::fixed << "To sell " << _value << " => " << (1 + _recession) * _base << " < " << _base << " > " << (1 + _top_break) * _base << std::endl;

            // update base while the value is rissing
            if (getIndex() > _top_break)
            {
                // updateBase
                std::cout << "Update the base: Rising " << _value << std::endl;
                updateBase();
            }

            // if last_entry > x or last_entry < x --> Sell
            if (getIndex() < _recession)
            {
                // sell the order
                benefit = (order * _value * (1 - _commission)) - _investment; // simulate the sell
                benefits_acc += benefit;

                // manage position
                _open_position = false;

                // updateBase
                std::cout << "\nSelling my position: " << order << " bitcoints. Actual value: " << _value << ". Benefits = " << benefit << " $." << std::endl;
                std::cout << "\nTOTAL BENEFITS: " << benefits_acc << "$. " << benefits_acc / investment_acc * 100 << "%. " << computedData << std::endl;
                updateBase();
            }
        }
    }
}

void Strategy::SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic)
{
    _cryptoGraphic = cryptoGraphic;
}

void Strategy::SetCryptoGuiPanelHandle(std::shared_ptr<CryptoGuiPanel> cryptoGuiPanel)
{
    _cryptoGuiPanel = cryptoGuiPanel;
}