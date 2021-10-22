#include <iostream>
#include <fetch_data.h>
#include <future>


int main() {
    std::cout << "Hello World!" << "\n";

    FetchData* data = new FetchData();

    std::thread t =std::thread(&FetchData::fetchData, data);

    t.join();
    
    return 0;
}