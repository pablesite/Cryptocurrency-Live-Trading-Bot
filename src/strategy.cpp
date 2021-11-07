#include <string>
#include <vector>
#include <iostream>
// #include <chrono>
// #include <future>
#include <deque>

#include "strategy.h"
#include "simulate_data.h"
#include "message_queue.h"

using std::string;
using std::vector;

Strategy::Strategy()
{

    std::cout << "Constructor of Strategy " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

void Strategy::cryptoBot(std::shared_ptr<SimulateData> data)
{

    std::cout << "CryptoBot working " << std::endl;

    bool open_position = false;
    double commission = 0.00075;
    double entry = 2 * 0.00075; // to make robust my positions
    double rupture = 0.0025;
    double recession = -0.0015;
    double invest_qty = 0.004;
    double lookbackperiod = 60;

    double base;
    double actual_value;
    double order;
    double benefits;
    double benefits_acc = 0;

    double count = 0;
    double invest;

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

    base = data->retrieveData(lookbackperiod);
    invest = invest_qty * base;

    while (true)
    {
        
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // retrieve data
        actual_value = data->retrieveData(lookbackperiod);
        count += 1;
        

        // to update base if the trend is negative
        if ((actual_value / base - 1) < - entry * 2)
        {
            std::cout << "Update the base: Descending " << actual_value << " " << std::endl;
            base = actual_value;
        }

        // to make an order
        if ((actual_value / base - 1) > entry)
        {
            order = invest_qty * (1 + commission) * actual_value * (actual_value / base); //simulate the bought
            std::cout << std::endl << "Buying my position " << invest_qty << " bitcoint. Actual value: " << actual_value << ". Order = " << order << " $. " << std::endl;
        
            base = actual_value; // Define new base
            open_position = true;
            //break;
        }

        // to return the order
        if (open_position == true)
        {
            while (true)
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(30));

                // retrieve data
                // if (data->returnData().size() > 0)
                // {
                //     std::cout << "Data received in second loop: " << data->returnData().back() << std::endl; //a lock is needed.
                //     actual_value = data->returnData().back();
                // }

                actual_value = data->retrieveData(lookbackperiod);
                count += 1;

                // update base while the value is rissing
                if ((actual_value / base - 1) > rupture)
                {
                    std::cout << "Update the base: Rising " << actual_value << std::endl;
                    base = actual_value; // Define new base
                }

                // std::cout << "actual_value: " << actual_value << " base " << base << " " << actual_value / base << std::endl;
                // if last_entry > x or last_entry < x --> Sell
                if ((actual_value / base - 1) < recession)
                {

                    benefits = (invest_qty * actual_value * (1 - commission)) - order; //simulate the sell
                    std::cout << std::endl << "Selling my position: " << invest_qty << " bitcoint. Actual value: " << actual_value << ". Benefits = " << benefits << " $." << std::endl;

                    base = actual_value; // Define new base
                    open_position = false;
                    benefits_acc += benefits;
                    std::cout << std::endl << "TOTAL BENEFITS: " << benefits_acc << "$. " << benefits_acc/invest*100 << "%. " << count <<std::endl << std::endl;
                    break;
                }
            }
        }

    }

    return;
}
