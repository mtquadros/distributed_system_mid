cmake_minimum_required(VERSION 3.28)
project(distributed_group)

set(CMAKE_CXX_STANDARD 20)
set(PNAME dsmodule)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_BUILD_TYPE Debug)
set(BOOST_DIR /home/dev/Projects/boost_1_85_0)

include_directories(${BOOST_DIR})
add_executable(${PNAME} main.cpp dsServer.cpp dsClient.cpp manageTable.cpp)

target_include_directories(${PNAME} PUBLIC ${BOOST_DIR})
target_include_directories(${PNAME} PUBLIC /home/dev/Projects/distributed_consensus/)

#add_library(dslib STATIC dsServer.cpp dsClient.cpp)
#
#target_include_directories(dslib PUBLIC ${BOOST_DIR})

#target_link_libraries(${PNAME} dslib)



