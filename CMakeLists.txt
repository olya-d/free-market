cmake_minimum_required(VERSION 2.8.4)
project(FreeMarket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include/jsoncpp)
include_directories(Substitutes)

set(SOURCE_FILES
    main.cpp
    Substitutes/SubstitutesConsumer.cpp
    Substitutes/SubstitutesMarket.cpp
    Substitutes/SubstitutesProducer.cpp
    Substitutes/SubstitutesSimulationConfig.cpp
    Substitutes/SubstitutesSimulationConfig.h
    Substitutes/SubstitutesConsumer.h
    Substitutes/SubstitutesMarket.h
    Substitutes/SubstitutesProducer.h
    BaseSimulationConfig.h
    BaseSimulationConfig.cpp
    SimulationConfigReader.cpp
    SimulationConfigReader.h
    OneGoodProducer.cpp
    OneGoodProducer.h
    OneGoodConsumer.cpp
    OneGoodConsumer.h
    OneGoodMarket.cpp
    OneGoodMarket.h
    Constants.cpp
    Constants.h
)


add_executable(FreeMarket ${SOURCE_FILES} OneGoodSimulationConfig.cpp OneGoodSimulationConfig.h)
target_link_libraries(FreeMarket /usr/local/lib/libjsoncpp.dylib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json
    ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
