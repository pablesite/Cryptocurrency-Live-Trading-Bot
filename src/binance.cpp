#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <deque>

#include <curl/curl.h>
#include <json/json.h>
#include <iomanip>

#include "binance.h"
#include "message_queue.h"

using std::string;
using std::vector;

Binance::Binance()
{
    // Constructor of Binance

    _mqData = std::make_shared<MessageQueue<double>>();
    // GET for Bitcoint in Binance
    configureAPI("https://api.binance.com/api/v3/ticker/price?symbol=BTCBUSD");

    std::cout << "Constructor of Binance " << std::endl;
}

double Binance::retrieveData(double &lookbackperiod)
{
    double value = 0;
    std::deque<double> data = _mqData->MessageQueue::receive(lookbackperiod);

    for (int i = 0; i < lookbackperiod; i++)
    {
        value += data[i];
    }
    
    return value / lookbackperiod;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void Binance::configureAPI(const char *URL)
{
    _curl = curl_easy_init();
    if (_curl)
    {
        struct curl_slist *headers = NULL;
        curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(_curl, CURLOPT_URL, URL);
        curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(_curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_readBuffer);
    }
    //curl_easy_cleanup(_curl);
}

void Binance::fetchData()
{
    std::cout << "Generating data " << std::endl;

    // How many data is fetched?
    double dataFetched = 0;

    // Json management
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    JSONCPP_STRING err;
    Json::Value jsonValue;
    double curlTotalTime;

    // Init watch
    long long cycleDuration = 1000; //1 sec.
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    lastUpdate = std::chrono::system_clock::now();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // Compute time difference to stop watch
        auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

        if (timeSinceLastUpdate >= cycleDuration)
        {
            _res = curl_easy_perform(_curl);
            if (_res == CURLE_OK)
            {
                const auto rawJsonLength = static_cast<int>(_readBuffer.length());
                _res = curl_easy_getinfo(_curl, CURLINFO_TOTAL_TIME, &curlTotalTime);
                if (_res == CURLE_OK)
                {
                    if (!reader->parse(_readBuffer.c_str(), _readBuffer.c_str() + rawJsonLength, &jsonValue,
                                       &err))
                    {
                        std::cout << "error" << std::endl;
                    }
                     std::cout << "data generated: " << _readBuffer << std::endl;  //DEBUG
                    _mqData->MessageQueue::send(std::stod(jsonValue["price"].asString()));
                    _readBuffer = "";
                    dataFetched += 1;
                }
            }

            // Adjust cycleDuration and reset lastUpdate for next cycle
            cycleDuration = 1000 - (timeSinceLastUpdate - cycleDuration) - (long)curlTotalTime * 1000;
            lastUpdate = std::chrono::system_clock::now();
        }
    }

    return;
}
