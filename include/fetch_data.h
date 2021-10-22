#ifndef FETCH_DATA_H
#define FETCH_DATA_H

// #include <fstream>
// #include <regex>
#include <string>
#include <vector>
//#include "binance.h"

/*
Basic class for Fetch Data of Cryptoconcurrency
It contains relevant attributes as shown below
*/
class FetchData {
 public:
  FetchData();
  void fetchData();
//   int Pid();                             
//   std::string User();                     
//   std::string Command();                   
//   float CpuUtilization();                  
//   std::string Ram();                      
//   long int UpTime();                       
//   bool operator<(Process const& a) const;  // TODO: See src/process.cpp

//   void setActiveJiffiesPrev(long active_jiffies_prev);
//   long getActiveJiffiesPrev();

 private:
    
    //Binance _bin;
    
    
    // int pid_;
    // std::string user_;
    // long total_time_prev_{0};  //ELIMINAR
    // long active_jiffies_prev_{0};     
    // long seconds_prev_{0};       
    // float cpu_utilization_{0.0};
    // std::vector<long> active_jiffies_acc_;
};

#endif