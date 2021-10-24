#include <string>
#include <vector>
#include <iostream>
// #include <chrono>
// #include <future>
#include <deque>

#include "strategy.h"
#include "simulate_data.h"

using std::string;
using std::vector;

Strategy::Strategy()
{

    std::cout << "Constructor of Strategy " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

void Strategy::cryptoBot(std::deque<double> data)
{

    std::cout << "CryptoBot working " << std::endl;

    bool open_position = false;

    while (true)
    {
        //Read data
        //std::cout << "Data returned: " << data.back() << std::endl; //a lock is needed.
        std::cout << "Data returned: "  << std::endl;

        // Obtain cumret

        // if not open position
        // if cumret > entry --> Buy
        // if (cumret > entry)
        // {
        //     open_position = true;
        //     break;
        // }
    }

    // if open poisiton
    if (open_position == true) {
        while (true) {
            // Read data

            // Obtain last_entry  

            // if last_entry > x and last_entry < x --> Sell  

            break;
        }
    }


    return;
}
