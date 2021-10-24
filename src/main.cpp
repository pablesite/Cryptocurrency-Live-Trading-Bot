#include <iostream>
#include <simulate_data.h>
#include <future>


int main() {
    std::cout << "Hello World!" << "\n";

    SimulateData* data = new SimulateData();

    std::thread t =std::thread(&SimulateData::fetchData, data);

    t.join();
    
    return 0;
}