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

void Strategy::cryptoBot(std::shared_ptr<SimulateData> data, double myCoin)
{

    std::cout << "CryptoBot working " << std::endl;

    bool open_position = false;
    double val;

    while (true)
    {
        //Read data
        //std::lock_guard<std::mutex> lock(SimulateData::_mutexSD);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        //En vez de esperar x tiempo, debe leer una cola de mensajes que lea cuando haya dato en la cola. Como los semáforos...
        // Quizá lo más inteligente es  hacer un lector de colas en la clase simulate_data
        //std::unique_lock<std::mutex> lck(_mtxMQ);
        //_cdtMQ.wait(lck, [this] { return !_queue.empty(); });
       
       
        if( data->returnData().size() > 0 ) {
            std::cout << "Data returned: " << data->returnData().back() << std::endl; //a lock is needed.
            val = data->returnData().back();
        }
        
        if (val > (1 + 0.0015) * + myCoin) {
            std::cout << "A comprar! "  << std::endl;
            break;
        }
       

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
