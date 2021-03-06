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
    Complements/ComplementsMarket.h
    Complements/ComplementsMarket.cpp
    Complements/ComplementsConsumer.h
    Complements/ComplementsConsumer.cpp
    Complements/ComplementsProducer.h
    Complements/ComplementsProducer.cpp
    Complements/ComplementsSimulationConfig.h
    Complements/ComplementsSimulationConfig.cpp
    BaseSimulationConfig.h
    BaseSimulationConfig.cpp
    SimulationConfigReader.cpp
    SimulationConfigReader.h
    OneGood/OneGoodProducer.cpp
    OneGood/OneGoodProducer.h
    OneGood/OneGoodConsumer.cpp
    OneGood/OneGoodConsumer.h
    OneGood/OneGoodMarket.cpp
    OneGood/OneGoodMarket.h
    OneGood/OneGoodSimulationConfig.h
    OneGood/OneGoodSimulationConfig.cpp
    MultipleGoods/MultipleGoodsMarket.h
    MultipleGoods/MultipleGoodsSimulationConfig.h
    MultipleGoods/MultipleGoodsSimulationConfig.cpp
)


add_executable(FreeMarket ${SOURCE_FILES} config.json)
target_link_libraries(FreeMarket /usr/local/lib/libjsoncpp.dylib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json
    ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
