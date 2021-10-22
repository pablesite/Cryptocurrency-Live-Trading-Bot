cmake_minimum_required(VERSION 3.7)

project(CryptoTradingBot)

file(GLOB SOURCES "src/*.cpp")
add_executable(CryptoTradingBot ${SOURCES})
#add_executable(HelloWorld src/main.cpp)
target_include_directories(CryptoTradingBot PUBLIC include)

# add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# set_property(TARGET monCryptoTradingBotitor PROPERTY CXX_STANDARD 17)

# target_link_libraries(CryptoTradingBot ${CURSES_LIBRARIES})
# # TODO: Run -Werror in CI.
# target_compile_options(CryptoTradingBot PRIVATE -Wall )