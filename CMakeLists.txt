cmake_minimum_required(VERSION 2.8.4)
project(FreeMarket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include/jsoncpp)

set(SOURCE_FILES
    Constants.h
    Consumer.cpp
    Consumer.h
    main.cpp
    Market.cpp
    Market.h
    Producer.cpp
    Producer.h)


add_executable(FreeMarket ${SOURCE_FILES})
target_link_libraries(FreeMarket /usr/local/lib/libjsoncpp.dylib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json
    ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
