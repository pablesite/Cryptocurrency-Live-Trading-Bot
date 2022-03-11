#include "historic_data.h"

// constructor
HistoricData::HistoricData()
{
    _mqData = std::make_shared<MessageQueue<double>>();
}

// retrieve Data from message queue. Median of data with a size of lookbackperiod
double HistoricData::retrieveData(int &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
    }

    return value / lookbackperiod;
}

// fetch data from historical data
void HistoricData::fetchData()
{
    // configure working directory
    namespace fs = std::filesystem;
    char *working_directory = "../historicData/";

    // go into every files in working directory. FOR THE FUTURE: Replace directory_iterator because the iteration order is unspecified.
    for (const auto &file_date : fs::directory_iterator(working_directory))
        for (const auto &file : fs::directory_iterator(file_date))
        {
            // declare some necessary strings
            std::string line, date, value;

            // open file
            std::ifstream file_stream(file.path());

            // init watch
            long long cycleDuration = 500000; //0.5 secs.
            std::chrono::time_point<std::chrono::system_clock> lastUpdate;
            lastUpdate = std::chrono::system_clock::now();

            if (file_stream.is_open())
            {   // always check whether the file is open
                while (file_stream)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    // compute time difference to stop watch
                    auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - lastUpdate).count();
                    if (timeSinceLastUpdate >= cycleDuration)
                    {
                        // get line
                        std::getline(file_stream, line);
                        std::istringstream linestream(line);
                        // obtain date and value of each line
                        while (linestream >> date >> value)
                        {
                            _mqData->MessageQueue::send(std::move(std::stod(value)));
                        }
                        // update lastUpdate for next cycle
                        lastUpdate = std::chrono::system_clock::now();
                    }
                }
            }
            else
                std::cout << "Unable to open file";
        }
}

// creation of files with historical data
void HistoricData::createHistoricData(std::shared_ptr<Binance> data)
{
    // this will be always 1 in this method in order to retrieve raw data from Binance.
    int lookbackperiod = 1;

    // data to be saved in file
    std::string ref_time;
    double actual_value;

    // create working directory if this doesn't exist.
    namespace fs = std::filesystem;
    char *working_directory = "../historicData/";
    fs::create_directories(working_directory);

    //g et actual time
    std::time_t now = std::time(0);
    std::tm *now_tm = std::localtime(&now);

    // prepare strings of dates
    std::string day = std::to_string(now_tm->tm_mday);
    std::string hour = std::to_string(now_tm->tm_hour);
    std::string date = std::to_string(now_tm->tm_year + 1900) + "_" + std::to_string(now_tm->tm_mon + 1) + "_" + day + "/";
    std::string file_name = hour + "_00.txt";

    // create directory for each day
    fs::create_directories(working_directory + date);

    // open file for each hour
    std::ofstream file(working_directory + date + file_name);

    while (true)
    {
        // update the time
        now = std::time(0);
        now_tm = std::localtime(&now);

        // check if the hour has changed
        if (hour != std::to_string(now_tm->tm_hour))
        {
            // close the file of the hour before.
            file.close();

            // check if the day has changed
            if (day != std::to_string(now_tm->tm_mday))
            {
                // create a directory for the new day
                date = std::to_string(now_tm->tm_year + 1900) + "_" + std::to_string(now_tm->tm_mon + 1) + "_" + std::to_string(now_tm->tm_mday) + "/";
                fs::create_directories(working_directory + date);

                // update the day
                day = std::to_string(now_tm->tm_mday);
            }

            // create a file with the new hour
            file_name = OutputFormat(now_tm->tm_hour) + "_00.txt";
            file.open(working_directory + date + file_name, std::ios::out | std::ios::trunc);

            // update the hour
            hour = std::to_string(now_tm->tm_hour);
        }

        if (file.is_open())
        {
            // retrieve new data
            actual_value = data->retrieveData(lookbackperiod);
            // new time for the new data
            ref_time = OutputFormat(now_tm->tm_hour) + ":" + OutputFormat(now_tm->tm_min) + ":" + OutputFormat(now_tm->tm_sec);
            // save into file
            file << std::setprecision(8) << std::fixed << ref_time << " " << actual_value << "\n";
        }
        else
        {
            std::cout << "\nUnable to open file. ";
            break;
        }
    }
    return;
}


// helper function
std::string HistoricData::OutputFormat(int unit_time)
{
    if (unit_time < 10)
    {
        return "0" + std::to_string(unit_time);
    }
    else
    {
        return std::to_string(unit_time);
    }
}
