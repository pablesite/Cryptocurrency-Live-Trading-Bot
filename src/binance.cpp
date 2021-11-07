#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <deque>

#include <curl/curl.h>
#include "binance.h"
#include "message_queue.h"

using std::string;
using std::vector;

Binance::Binance()
{
    _mqData = std::make_shared<MessageQueue<double>>();

    std::cout << "Constructor of FetchData " << std::endl;
    // Constructor of Binance
    //_bin (Binance);
}

double Binance::retrieveData(double &lookbackperiod)
{
    // Aquí debo ver cómo cojo todo el vector... en el receive de la cola no sería porque necesito los datos en la siguiente iteración
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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Binance::fetchData(double myCoinBase)
{
    //double data;
    // Connect with Binance
    //_bin.connect();

    // Fetch Data
    //_bin.fetch();

    std::cout << "Generating data " << std::endl;

    // return data from the server
    // struct return_string
    // {
    //     char *ptr;
    //     size_t len;
    // };

    double x = myCoinBase;
    double count = 0;

    CURL *curl;
    CURLcode res;
    // struct return_string s;
    // s.len = 0;
    // s.ptr = (char *)calloc(1, s.len + 1);
    // if (s.ptr == NULL)
    // {
    //     fprintf(stderr, "init_string malloc() failed\n");
    //     exit(-1);
    // }
    // s.ptr[0] = '\0';
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=BTCBUSD");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        //curl_easy_perform(curl);
    }
    //curl_easy_cleanup(curl);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        res = curl_easy_perform(curl);
        

        std::cout << "meto un dato a la cola: " << readBuffer << " " << count << std::endl;
        //_mqData->MessageQueue::send(std::move(res));
        readBuffer = "";
        count += 1;
    }

    return;
}
