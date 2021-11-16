#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
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

// Esta función es igual en todas las clases. Implementarla en fetch_data class (clase padre)
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

std::string HistoricData::OutputFormat(int unit_time) {
  if (unit_time < 10) {
    return "0" + std::to_string(unit_time);
  } else {
    return std::to_string(unit_time);
  }
}

void HistoricData::createHistoricData(std::shared_ptr<Binance> data)
{
    
    double actual_value;
    double lookbackperiod = 1;
    int count = 0;

    // std::chrono::time_point<std::chrono::system_clock> dateData;
    // dateData = std::chrono::system_clock::now();
    // std::time_t dateData_time = std::chrono::system_clock::to_time_t(dateData);
       
    std::time_t now = std::time(0);

    std::tm *now_tm = std::localtime(&now);
    //char *dt = std::ctime(&now);
    std::string date = std::to_string(now_tm->tm_mday) + "_" + std::to_string(now_tm->tm_mon + 1) + "_" + std::to_string(now_tm->tm_year + 1900) + ".txt";
    std::string time;

    std::ofstream myfile(date);
    
    if (myfile.is_open())
    {
        while (count < 28800) // 8horas
        {
            // retrieve new data
            actual_value = data->retrieveData(lookbackperiod);
            
            // new time
            now = std::time(0);
            now_tm = std::localtime(&now);
            time = OutputFormat(now_tm->tm_hour) + ":" + OutputFormat(now_tm->tm_min) + ":" + OutputFormat(now_tm->tm_sec);

            // save into file
            myfile << std::setprecision(8) << std::fixed << time << " " << actual_value << "\n";
            count++;
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";

    return;
}

void HistoricData::fetchData()
{

    std::cout << "Reading data from a file " << std::endl;

    //std::filesystem::path myPath = std::filesystem::current_path().string() + "\\bitcoin.txt";
    //std::ifstream myfile("C:\\Users\\pablo\\proyectos\\udacity-trainning\\Cryptocurrency-Live-Trading-Bot\\src\\bitcoin.txt");
    std::ifstream myfile("bitcoin.txt");
    std::string myline;

    // Init watch
    long long cycleDuration = 1000; // Change that to improve speed in reading data
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    lastUpdate = std::chrono::system_clock::now();

    if (myfile.is_open())
    { // always check whether the file is open
        while (myfile)
        {

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            // Compute time difference to stop watch
            auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

            if (timeSinceLastUpdate >= cycleDuration)
            {
                // myfile >> mystring;
                // pipe file's content into stream
                std::getline(myfile, myline);
                std::cout << myline << '\n';
                _mqData->MessageQueue::send(std::move(std::stod(myline)));

                // std::cout << mystring << std::endl; // pipe stream's content to standard output

                // Update lastUpdate for next cycle
                lastUpdate = std::chrono::system_clock::now();
            }
        }
    }
    else
        std::cout << "Unable to open file";

    return;
}
