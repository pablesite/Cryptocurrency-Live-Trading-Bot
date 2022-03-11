# CPPND: Capstone - Cryptocurrency Live Trading Simulated Bot

This is a repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
In this project, I try to demostrate the principles I have learned throughout this Nanodegree Program. 

# Which project is chosen
I have chosen the first option, i.e., to build the project of my choice. In this case I have chosen an application to build a Cryptocurrency Live Trading Simulated Bot. Referred to in the text from now on as: **CryptoBot**.


## Description about the project
Crypto Bot is a simulator to test different decision algorithms (named as strategies) to make an automatic trading with cryptos.

### How it works
CryptoBot is based on a graphical user interface where you can interact with:
-  Selection of **general parameters**.
You can select the **exchange platform**, the **cryptocurrency**, the **strategy** to use and the **quantity of your investment**.
Note: This option is mocked --> To work in the future. The idea is to include several exchange platforms, several cryptocurrencies and above all several strategies to maximize the gains.
By default, CryptoBot works with: Binance, Bitcoint, Standard Strategy and 50 $.
- Selection of **inputs parameters** of the standard strategy
The strategy programmed is named 'standar strategy' and is based basically in trends. This strategy needs the following parameters:
    - (Double) **Commission**: Commission in Binance for buying/selling trades. 
    - (Bool) **Open Position**: True/False. It indicates if there is a trade done.
    - (Double) **Entry**: Threshold value in positive trend to perform a trade.
    - (Double) **Bottom Break**: Threshold value in negative trend to update base value.
    - (Double) **Recession**: Threshold value in negative trend to sell the trade.
    - (Double) **Top Break: Threshold value in positive trend to update base value.
    - (Int) **Look Back Period**: Period of time (in seconds) that are used to average the input values to the strategy.

    In this way, the **standard strategy** works in the following way:
    Open Position = False --> If the trend is up, you trade --> Open Position = True. In that case, while the trend is rising, the base value on which you calculate the threshold is updated. The moment the trend is down, sell. If it has raised enough you win money; otherwise you lose a little.
    Open Position = False --> If the trend is down, the base value is updated to apply the thresholds on an updated value. In this case you have not invested anything, so you neither lose nor win.

    Note: The input setting for the strategy in the menu is mocked.--> To work in the future. Meanwhile you can change this values in 'strategy.h'. In this moment, this values are sets to: 
    `double _entry = 2.0 * _commission;`
    `double _bottomBreak = -1.5 * _commission;`
    `double _recession = -1.25 * _commission;`
    `double _topBreak = 1.0 * _commission;`
    `int _lookBackPeriod = 5;`

- **Start/Stop of three types of simulations**. Each of the three types works in a similar way. Two threads are launched at the same time: one to fetch data and store it in a shared queue (message_queue), and another to get the data from the queue when it is available and apply the logic of the strategy.
    - With **simulated data**: A function has been programmed that randomly simulates data trying to simulate the behavior of a cryptocurrency.
    - With **historical data**: A functions that read data from a textfile has been developed. In this way different configuration parameters in the strategy can be tested with the same input data in order to compare results.
    - With **real data in real time**: A request to API from Binance is used to fetch real data in real time. In this case we can simulate our strategy in a real case in real time.

-  **Create historical Data**. Functionallity to create historical data in a text file. A request to API from Binance is used in order to fetch real data from Bitcoint in real time. 

Below you can see an example that show how it works with historical data.

![](https://github.com/pablesite/Cryptocurrency-Live-Trading-Bot/blob/master/images/CryptoBotPicture.png){width='600px'}


## Dependencies for Running Locally (TO UPDATE)
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* curl
  * Windows: recommended installed with vpckg
  * Linux: sudo apt install curl && sudo apt-get install libcurl4-openssl-dev
* jsoncpp
  * Windows: recommended installed with vpckg
  * Linux: sudo apt-get install libjsoncpp-dev
* wxwidgets
  * Windows: recommended installed with vpckg
  * Linux: sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5

## Basic Build Instructions (TO UPDATE)
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./CryptoTradingBot`.

## Class Structure
To upload with some schemas
Esquema drawio

## Information about each rubric point addressed

### Compiling and Testing
- The submission must compile and run: **Check**
Project use cmake and make and is prepared for both Unix and Windows system.

### Loops, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures: **Check**
Project use control structures likes if..else, while, for, etc in several functions along all the classes.

- The project reads data from a file and process the data, or the program writes data to a file: **Check** 
The project uses functions to save and read data in a text file. In:
`void HistoricData::createHistoricData(std::shared_ptr<Binance> data);`
`void HistoricData::fetchData()`

- The project accepts user input and processes the input: **Check** 
There is a pre-build version of the GUI that was started by console input.
Commented out in `main.cpp`


### Object Oriented Programming
- The project uses Object Oriented Programming techniques: **Check**
Different classes are used to build the GUI, to generate different types of data, and to apply the strategy logic.

- Classes use appropriate access specifiers for class members: **Check**
All class data members are explicitly specified as public, protected, or private

- Class constructors utilize member initialization lists: **Check**
All class members that are set to argument values are initialized through member initialization lists. For example, in:
`strategy.cpp`

- Classes abstract implementation details from their interfaces: **Check**
All class member functions document their effects, either through function names, comments, or formal documentation.

- Classes encapsulate behavior:  **Check**
Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions. For example, in `strategy.h`

- Classes follow an appropriate inheritance hierarchy:  **Check**
Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified. For example, `FetchData` is an abstract class inherited by the classes that fetched data; and these override the methods of the first one.

- Overloaded functions allow the same function to operate on different parameters: **Check**
One function is overloaded with different signatures for the same function name. For example, in `constructor of strategy.h`

- Derived class functions override virtual base class functions: **Check**
One member function in an inherited class overrides a virtual base class member function. For example, in: SimulateData.h --> `void fetchData() override;`

- Templates generalize functions in the project: **Check**
One function is declared with a template that allows it to accept a generic parameter. For example in: CryptoGuiPanel --> `template <class T> void StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stopBtn);`

### Memory management
- The project makes use of references in function declarations: **Check**
At least two variables are defined as references, or two functions use pass-by-reference in the project code. FOr example in: `double retrieveData(double &lookbackperiod);` or in ` CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size);`

- The project uses destructors appropriately: TODO
[At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.]

- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: TODO
[The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.]

- The project follows the Rule of 5: TODO
[For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.]

- The project uses move semantics to move data, instead of copying it, where possible: **Check**
For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. For example in: historic_data.cpp --> `_mqData->MessageQueue::send(std::move(std::stod(value)));`

- The project uses smart pointers instead of raw pointers: **Check**
The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. For example in: binance.h --> `std::shared_ptr<MessageQueue<double>> _mqData;`


### Concurrency
- The project uses multithreading: **Check**
The project uses multiple threads in the execution. For example in: `void CryptoGuiPanel::StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stopBtn)`

- A promise and future is used in the project: **It has not been necessary.**

- A mutex or lock is used in the project: **Check**
A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code. In: `void CryptoGraphic::setActualValue(double value)`

- A condition variable is used in the project: **Check**
A std::condition_variable is used in the project code to synchronize thread execution. In: `message_queue.h`

