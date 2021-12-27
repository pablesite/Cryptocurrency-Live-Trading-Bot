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



void Strategy::cryptoBot()
{

    std::cout << "CryptoBot working " << std::endl;

    //this->SetCryptoLogicHandle(cryptoLogic);

    // investment data
    double invest_qty = 0.004;

    // data from binance
    double commission = 0.00075;

    // input strategy data
    double entry = 2 * commission; // to make robust my positions
    double rupture = commission/0.3;
    double recession = -2 * commission;
    double lookbackperiod = 1;

    // temporary strategy data
    bool open_position = false;
    double base;
    double actual_value;

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
    // rupture
    // recession

    // if % rupture (10 %) --> Buy position
    // order = invest_qty * (1 + % commission) * base price * (1 + % rupture)
    // order = 10 * (1 + 0.05) * 2 * (1.1) = 23.1€ //ME HA COSTADO 23.1€ invertir en 10 cryptos
    // order = 10 * (1 + 0.05) * 2 * (1.05) = 22.05€ //ME HA COSTADO 23.1€ invertir en 10 cryptos
    // order = 10 * (1 + 0.05) * 2 * (1.15) = 24.15€ //ME HA COSTADO 23.1€ invertir en 10 cryptos

    // if % rupture UP 10 % --> .....
    // ...
    // benefits = (invest_qty * base price * (1 + rupture)exp2 * (1 - % commission)) - order
    // benefits = (10 * 2 * (1 + 0.1)exp2 * 0.95) - 23.1 = -0.11
    //  benefits = (10 * 2 * (1 + 0.05)exp2 * 0.95) - 22.05 = 1.105
    //  benefits = (10 * 2 * (1 + 0.15)exp2 * 0.95) - 24.15 = 0.9775

    // if % recession DOWN 10 % --> Sell
    // benefits = (invest_qty * base price * (1 + rupture)* (1 - recession) * (1 - % commission)) - order
    // benefits = (10 * 2 * (1 + 0.1) * (1 - 0.1) * 0.95) - 23.1 = - 4.29

    // (1 + % commission)/(1 - % commission)  >  (1 + %rupture) //This is not too clear

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    base = getData(lookbackperiod);
    // _cryptoLogic->sendToLogic(base);
        std::cout << "data is: " << base << std::endl;
        //_cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::paintEvent)); 
       // _cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));  
    invest = invest_qty * base; // TO REVIEW...

    while (true)
    {

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // retrieve data
        actual_value = getData(lookbackperiod);
        _cryptoGraphic->setActualValue(actual_value);
        std::cout << "Graphics in Strategy2 is: " << _cryptoGraphic;
        //_cryptoGraphic->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));  

        //cryptologic->setDataFromStrategy(actual_value);
        count += 1;

        std::cout << std::setprecision(4) << std::fixed << "To buy " << actual_value << " => " << (1 - entry * 2) * base << " < " << base << " > " << (1 + entry) * base << std::endl;
        // to update base if the trend is negative
        if ((actual_value / base - 1) < -entry * 2)
        {
            std::cout << "Update the base: Descending " << actual_value << " " << std::endl;
            base = actual_value;
        }

        // to make an order
        if ((actual_value / base - 1) > entry)
        {
            order = invest_qty * (1 + commission) * actual_value * (actual_value / base); //simulate the bought
            std::cout << std::endl
                      << "Buying my position " << invest_qty << " bitcoint. Actual value: " << actual_value << ". Order = " << order << " $. " << std::endl;

            base = actual_value; // Define new base
            open_position = true;
            //break;
        }

        // to return the order
        if (open_position == true)
        {
            while (true)
            {

                // retrieve data
                actual_value = getData(lookbackperiod);
                count += 1;
                std::cout << std::setprecision(4) << std::fixed << "To sell " << actual_value << " => " << (1 + recession) * base << " < " << base << " > " << (1 + rupture) * base << std::endl;

                // update base while the value is rissing
                if ((actual_value / base - 1) > rupture)
                {
                    std::cout << "Update the base: Rising " << actual_value << std::endl;
                    base = actual_value; // Define new base
                }

                // if last_entry > x or last_entry < x --> Sell
                if ((actual_value / base - 1) < recession)
                {

                    benefit = (invest_qty * actual_value * (1 - commission)) - order; //simulate the sell
                    std::cout << std::endl
                              << "Selling my position: " << invest_qty << " bitcoint. Actual value: " << actual_value << ". Benefits = " << benefit << " $." << std::endl;

                    base = actual_value; // Define new base
                    open_position = false;
                    benefits_acc += benefit;
                    std::cout << std::endl
                              << "TOTAL BENEFITS: " << benefits_acc << "$. " << benefits_acc / invest * 100 << "%. " << count << std::endl
                              << std::endl;
                    break;
                }
            }
        }
    }

    return;
}

void Strategy::SetCryptoLogicHandle(std::shared_ptr<CryptoLogic> cryptoLogic) {
  _cryptoLogic = cryptoLogic;

}

void Strategy::SetCryptoGraphicHandle(CryptoGraphic * cryptoGraphic) {
    std::cout << "Seteo el ptr de cryptoGraphic" << std::endl;
    
    _cryptoGraphic = cryptoGraphic;
    std::cout << "Graphics in Strategy is: " << _cryptoGraphic;
}