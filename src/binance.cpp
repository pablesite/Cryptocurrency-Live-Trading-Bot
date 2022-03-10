#include "binance.h"

// constructor
Binance::Binance()
{
    _mqData = std::make_shared<MessageQueue<double>>();

    // GET for Bitcoint in Binance
    configureAPI("https://api.binance.com/api/v3/ticker/price?symbol=BTCBUSD");
}

// retrieve Data from message queue. Median of data with a size of lookbackperiod
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

// helper function
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// configure requiest of Binance API
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
}

// fetch data from binance
void Binance::fetchData()
{
    // how many data is fetched?
    double dataFetched = 0;

    // json management
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    JSONCPP_STRING err;
    Json::Value jsonValue;
    double curlTotalTime;

    // init watch
    long long cycleDuration = 1000; // 1 sec.
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    lastUpdate = std::chrono::system_clock::now();

    while (true)
    {
        // compute time difference to stop watch
        auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

        if (timeSinceLastUpdate >= cycleDuration)
        {
            // perform request and storage in _readBuffer
            _res = curl_easy_perform(_curl); 
            if (_res == CURLE_OK)
            {
                const auto rawJsonLength = static_cast<int>(_readBuffer.length());
                // obtain time of request
                _res = curl_easy_getinfo(_curl, CURLINFO_TOTAL_TIME, &curlTotalTime);
                if (_res == CURLE_OK)
                {
                    if (!reader->parse(_readBuffer.c_str(), _readBuffer.c_str() + rawJsonLength, &jsonValue,
                                       &err))
                    {
                        std::cout << "error" << std::endl;
                    }
                    // send to message queue the value of cryptoconcurrency
                    _mqData->MessageQueue::send(std::stod(jsonValue["price"].asString()));
                    _readBuffer = "";
                    dataFetched += 1;
                }
            }

            // adjust cycleDuration and reset lastUpdate for next cycle
            cycleDuration = 1000 - (timeSinceLastUpdate - cycleDuration) - (long)curlTotalTime * 1000;
            lastUpdate = std::chrono::system_clock::now();
        }
    }
}
