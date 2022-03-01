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
    _cryptoGraphic->setLimits();
}

void Strategy::cryptoBot()
{

    std::cout << "CryptoBot working " << std::endl;

    // this while is for avoid the rest of the strategy, because in there, there is some problem with core dump
    //  while (true)
    //  {
    //      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //      std::cout << "Crypto working " << std::endl;
    //  }

    // this->SetCryptoLogicHandle(cryptoLogic);

    // investment data
    double invest_qty = 0.004;

    // data from binance
    double commission = 0.00075;

    // input strategy data
    double entry = 1 * commission; // to make robust my positions
    double bottom_break = -2 * commission;

    double recession = -3*commission;
    double top_break = 6 * commission; //para asegurar beneficios, esto debería actualizarse el doble de cuando voy a vender... pensar mejor y hacer pruebas

    double lookbackperiod = 1;

    // temporary strategy data
    bool open_position = false;
    // double base;
    // double actual_value;

    // output strategy data
    double order;
    double benefit;
    double benefits_acc = 0;
    double invest;
    double count = 0;

    // base price (2€/crypto)
    // invest_qty ( 10 crypto)
    // % commission (5 %)
    // theoric value = invest_qty * base price
    // theoric value = 10 * 2 = 20 €
    // entry (value to buy)
    // top_break
    // recession

    // if % top_break (10 %) --> Buy position
    // order = invest_qty * (1 + % commission) * base price * (1 + % top_break)
    // order = 10 * (1 + 0.05) * 2 * (1.1) = 23.1€ //ME HA COSTADO 23.1€ invertir en 10 cryptos
    // order = 10 * (1 + 0.05) * 2 * (1.05) = 22.05€ //ME HA COSTADO 23.1€ invertir en 10 cryptos
    // order = 10 * (1 + 0.05) * 2 * (1.15) = 24.15€ //ME HA COSTADO 23.1€ invertir en 10 cryptos

    // if % top_break UP 10 % --> .....
    // ...
    // benefits = (invest_qty * base price * (1 + top_break)exp2 * (1 - % commission)) - order
    // benefits = (10 * 2 * (1 + 0.1)exp2 * 0.95) - 23.1 = -0.11
    //  benefits = (10 * 2 * (1 + 0.05)exp2 * 0.95) - 22.05 = 1.105
    //  benefits = (10 * 2 * (1 + 0.15)exp2 * 0.95) - 24.15 = 0.9775

    // if % recession DOWN 10 % --> Sell
    // benefits = (invest_qty * base price * (1 + top_break)* (1 - recession) * (1 - % commission)) - order
    // benefits = (10 * 2 * (1 + 0.1) * (1 - 0.1) * 0.95) - 23.1 = - 4.29

    // (1 + % commission)/(1 - % commission)  >  (1 + %top_break) //This is not too clear

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    _base = getData(lookbackperiod);

    _cryptoGraphic->setStrategyData(commission, entry, top_break, recession);
    _cryptoGraphic->setStrategyHandle(shared_from_this()); // Faltará hacer lo mismo con cryptoGuiPanel
    _cryptoGraphic->setLimits();

    invest = invest_qty * _base; // TO REVIEW...

    while (true)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //Para que las simulaciones vayan a tiempo real.

        // retrieve data
        _value = getData(lookbackperiod);
        _cryptoGraphic->setActualValue(_value);

        count += 1;

        if (open_position == false)
        {
            std::cout << std::setprecision(4) << std::fixed << "To buy " << _value << " => " << (1 - entry * 2) * _base << " < " << _base << " > " << (1 + entry) * _base << std::endl;
            // to update base if the trend is negative
            if (getIndex() < bottom_break)
            {
                // console log
                std::cout << "Update the base: Descending " << _value << " " << std::endl;

                updateBase();
            }

            // to make an order
            if (getIndex() > entry)
            {
                // perform an order
                order = invest_qty * _value * (1 + commission); // simulate the bought

                // console log
                std::cout << std::endl
                          << "Buying my position " << invest_qty << " bitcoint. Actual value: " << _value << ". Order = " << order << " $. " << std::endl;

                // manage position
                open_position = true;

                updateBase();
            }
        }
        else
        {
            std::cout << std::setprecision(4) << std::fixed << "To sell " << _value << " => " << (1 + recession) * _base << " < " << _base << " > " << (1 + top_break) * _base << std::endl;

            // update base while the value is rissing
            if (getIndex() > top_break)
            {
                // console log
                std::cout << "Update the base: Rising " << _value << std::endl;

                updateBase();
            }

            // if last_entry > x or last_entry < x --> Sell
            if (getIndex() < recession)
            {

                // sell the order
                benefit = (invest_qty * _value * (1 - commission)) - order; // simulate the sell
                benefits_acc += benefit;

                // console log
                std::cout << std::endl
                          << "Selling my position: " << invest_qty << " bitcoint. Actual value: " << _value << ". Benefits = " << benefit << " $." << std::endl;
                std::cout << std::endl
                          << "TOTAL BENEFITS: " << benefits_acc << "$. " << benefits_acc / invest * 100 << "%. " << count << std::endl
                          << std::endl;

                // manage position
                open_position = false;

                updateBase();
            }
        }
    }
}


void Strategy::SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic)
{
    _cryptoGraphic = cryptoGraphic;
    std::cout << "\n\nGraphics in Strategy is: " << _cryptoGraphic;
}

void Strategy::SetCryptoGuiPanelHandle(std::shared_ptr<CryptoGuiPanel> cryptoGuiPanel)
{
    // std::cout << "\n\nCRYPTOGUIPANEL in Strategy is: " << cryptoGuiPanel.get();
    _cryptoGuiPanel = cryptoGuiPanel;
    
}