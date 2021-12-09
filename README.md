# CPPND: Capstone Hello World Repo (TO UPDATE)

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.


# Which project is chosen

Cryptobot xx
## Description about the project
Cryptobot is a simulator to test some strategys to make an automatic trading with cryptos.
xxx


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

## Basic Build Instructions (TO UPDATE)
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./HelloWorld`.

## Expected behaviour
1. You need to select which crypto want to test.
2. You need to select an strategy...
3. You need to select real time or maximum velocity
4 ....

## Class Structure
To upload with some schemas


## Information about each rubric point addressed

### Compiling and Testing
- The submission must compile and run: Check
Project use cmake and make and is prepared for both Unix and Windows system.

### Loops, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures: Check
Project use control structures likes if..else, while, for, etc in several functions along all the classes.

- The project reads data from a file and process the data, or the program writes data to a file: xxx 
[The project reads data from an external file or writes data to a file as part of the necessary operation of the program]
I need to save data from bitcoint into a file and after that, i can use this data to test the strategy

- The project accepts user input and processes the input: xxx
[The project accepts input from a user as part of the necessary operation of the program]
I need to do 'interfaz' in main through cin in cmder.

### Object Oriented Programming
- The project uses Object Oriented Programming techniques: Check
[The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks]
xxx
- Classes use appropriate access specifiers for class members: Check
[All class data members are explicitly specified as public, protected, or private]
- Class constructors utilize member initialization lists: xxx
[All class members that are set to argument values are initialized through member initialization lists.]
- Classes abstract implementation details from their interfaces: xxxx
[All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways]
- Classes encapsulate behavior: TODO
[Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions]
- Classes follow an appropriate inheritance hierarchy: Check (Composition?)
[Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified]
- Overloaded functions allow the same function to operate on different parameters: XXX
[One function is overloaded with different signatures for the same function name]
- Derived class functions override virtual base class functions: Check
[One member function in an inherited class overrides a virtual base class member function]
xxx
- Templates generalize functions in the project: Check
[One function is declared with a template that allows it to accept a generic parameter]

### Memory management
- The project makes use of references in function declarations: xxx
[At least two variables are defined as references, or two functions use pass-by-reference in the project code.]
- The project uses destructors appropriately: TODO
[At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.]
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: TODO
[The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.]
- The project follows the Rule of 5: TODO
[For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.]
- The project uses move semantics to move data, instead of copying it, where possible: Check
[For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object]
xx
- The project uses smart pointers instead of raw pointers: Check
[The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.]
xx

### Concurrency
- The project uses multithreading: Check
[The project uses multiple threads in the execution]
xx
- A promise and future is used in the project: Check
[A promise and future is used to pass data from a worker thread to a parent thread in the project code]
xx
- A mutex or lock is used in the project: Check
[A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code]
xx
- A condition variable is used in the project: Check
[A std::condition_variable is used in the project code to synchronize thread execution]
xx
