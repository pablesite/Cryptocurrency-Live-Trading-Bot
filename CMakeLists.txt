cmake_minimum_required(VERSION 3.7)

project(CryptoTradingBot)

if (UNIX)
    add_definitions(-std=c++17) 
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif (UNIX)

if (WIN32)
    set(CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
endif (WIN32)

file(GLOB SOURCES "src/*.cpp")
add_executable(CryptoTradingBot ${SOURCES})


# ##### CURL STUFF INI #####
message(STATUS "Looking for curl...")
set(CURL_DIR "C:/Users/PabloRuiz/Proyectos/vcpkg/installed/x64-windows/share/curl")  #This could be better in environment file (.env)
find_package(CURL CONFIG REQUIRED)

if (CURL_FOUND)
    message(STATUS "Found curl version: ${CURL_VERSION_STRING}")
    message(STATUS "Using curl version: ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using curl libraries: ${CURL_LIBRARIES}\n")
    list(APPEND Project_INCLUDE_DIRS ${CURL_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Could not find curl.")
 endif()

#  target_link_libraries(CryptoTradingBot ${CURL_LIBRARIES})
# ##### CURL STUFF END #####

find_package(jsoncpp CONFIG REQUIRED)



find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
target_include_directories(CryptoTradingBot PRIVATE ${wxWidgets_INCLUDE_DIRS})
#target_link_libraries(CryptoTradingBot PRIVATE ${wxWidgets_LIBRARIES})

target_link_libraries(CryptoTradingBot PRIVATE jsoncpp_lib jsoncpp_object ${CURL_LIBRARIES} ${wxWidgets_LIBRARIES})


target_include_directories(CryptoTradingBot PUBLIC include)





