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

void HistoricData::createHistoricData(std::shared_ptr<Binance> data)
{
    std::ofstream myfile("bitcoin.txt");
    double actual_value;
    double lookbackperiod = 1;
    int count = 0;

    // std::chrono::time_point<std::chrono::system_clock> dateData;
    // dateData = std::chrono::system_clock::now();
    // std::time_t dateData_time = std::chrono::system_clock::to_time_t(dateData);
    // std::cout << std::ctime(&dateData_time) << std::endl;

    // time_t tmNow;
    // tmNow = time(NULL);
    // struct tm t = *localtime(&tmNow);
    // std::cout << "Current Time: " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << 'test' << std::endl;


    // std::tm time_in = {0, 0, 0,             // second, minute, hour
    //                    9, 10, 2016 - 1900}; // 1-based day, 0-based month, year since 1900
    std::time_t time_temp = std::time(0);
    //Note: Return value of localtime is not threadsafe, because it might be
    // (and will be) reused in subsequent calls to std::localtime!
    const std::tm *time_out = std::localtime(&time_temp);
    //Sunday == 0, Monday == 1, and so on ...
    std::cout << "Date:" << time_out->tm_mday << "/" << time_out->tm_mon+1 << "/" << time_out->tm_year+1900 << " " << time_out->tm_hour << ":" << time_out->tm_min << ":" << time_out->tm_sec <<"\n";
    std::cout << "\n";


    std::time_t now = std::time(0);
    char *dt = std::ctime(&now);
    std::cout << "Todays Date is " << dt << '\n';

    if (myfile.is_open())
    {
        while (count < 100)
        {

            actual_value = data->retrieveData(lookbackperiod);
            // std::cout <<  std::setprecision(8) < < std::fixed << "test before retrieveData:" << actual_value << std::endl;
            now = std::time(0);
            dt = std::ctime(&now);

            myfile << std::setprecision(8) << std::fixed << dt << " " << actual_value << "\n";
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
