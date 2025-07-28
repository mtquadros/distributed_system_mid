cmake_minimum_required(VERSION 3.31)
project(distributed_group)

set(CMAKE_CXX_STANDARD 20)
set(PNAME dsmodule)
set(BOOST_DIR /home/dev/Projects/boost_1_85_0)

include_directories(${BOOST_DIR})
add_executable(${PNAME} main.cpp dsServer.cpp dsClient.cpp printTable.cpp)

target_include_directories(${PNAME} PUBLIC ${BOOST_DIR})
target_include_directories(${PNAME} PUBLIC /home/dev/Projects/distributed_consensus/)

#add_library(dslib STATIC dsServer.cpp dsClient.cpp)
#
#target_include_directories(dslib PUBLIC ${BOOST_DIR})

#target_link_libraries(${PNAME} dslib)



