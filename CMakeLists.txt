cmake_minimum_required(VERSION 3.14.5)
project(YTaxiPlot)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(YTaxiPlot main.cpp plot.hpp plot.cpp graph.cpp details.hpp details.cpp)

target_link_libraries(YTaxiPlot sfml-graphics sfml-audio)


set(boost_min_ver 1.50.0)
set(boost_libs system filesystem)
find_package(Boost ${boost_min_ver})

if(Boost_FOUND)
    find_package(Boost ${boost_min_ver} COMPONENTS ${boost_libs})
endif()

target_link_libraries(YTaxiPlot ${Boost_LIBRARIES})