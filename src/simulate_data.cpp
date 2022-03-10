#include "simulate_data.h"

// constructor
SimulateData::SimulateData()
{
    _mqData = std::make_shared<MessageQueue<double>>();
}

// retrieve Data from message queue. Median of data with a size of lookbackperiod
double SimulateData::retrieveData(double &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
    }

    return value / lookbackperiod;
}

// fetch data from data simulated
void SimulateData::fetchData()
{
    // how many data is fetched?
    double count = 0;

    double myCoinBase = 50000; 
    double x = myCoinBase;
    
    // init watch
    long long cycleDuration = 50; //0.5 secs
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    lastUpdate = std::chrono::system_clock::now();

    while (true)
    {
        // compute time difference to stop watch
        auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // with 999 there is a slight positive trend 
            x = x * (1 + (rand() % 2000 - 999) / 10000000.0);

            // send value to message queue
            _mqData->MessageQueue::send(std::move(x));
            count += 1;

            // update lastUpdate for next cycle
            lastUpdate = std::chrono::system_clock::now();
        }
    }

    return;
}
