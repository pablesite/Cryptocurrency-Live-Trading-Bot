#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <deque>
#include <fstream>
#include <filesystem>
// #include <unistd.h>


#include "historic_data.h"
#include "message_queue.h"

using std::string;
using std::vector;

std::mutex HistoricData::_mutexSD;

HistoricData::HistoricData()
{
    _mqData = std::make_shared<MessageQueue<double>>();

    std::cout << "Constructor of HistoricData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

double HistoricData::retrieveData(double &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    // std::cout << data.size() << std::endl;
    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
        // value += _mqData->receive();
    }

    return value / lookbackperiod;
}

void HistoricData::fetchData()
{
 
    std::cout << "Reading data from a file " << std::endl;

    //std::filesystem::path myPath = std::filesystem::current_path().string() + "\\bitcoin.txt";
    //std::ifstream myfile("C:\\Users\\pablo\\proyectos\\udacity-trainning\\Cryptocurrency-Live-Trading-Bot\\src\\bitcoin.txt");
    std::ifstream myfile("bitcoin.txt");
    
    std::string mystring;
    std::string myline;
    
    if (myfile.is_open())
    { // always check whether the file is open
        while (myfile)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
            // myfile >> mystring;
            // pipe file's content into stream
            std::getline(myfile, myline);
            std::cout << myline << '\n';
            _mqData->MessageQueue::send(std::move(std::stod(myline)));

            // std::cout << mystring << std::endl; // pipe stream's content to standard output
        }
    }

    return;
}
