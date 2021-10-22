#include <string>
#include <vector>
#include <iostream>

#include "fetch_data.h"


using std::string;
using std::to_string;
using std::vector;

// pid and user doesn't change during the execution of system monitor.
// pid dosn't need invariant and can be initialed directly.
FetchData::FetchData() {
    // cpu_utilization_ = CpuUtilization();
    std::cout << "Constructor of FetchData " << std::endl;
}

