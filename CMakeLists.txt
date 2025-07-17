cmake_minimum_required(VERSION 3.31)
project(distributed_group)

set(CMAKE_CXX_STANDARD 20)
set(PNAME dsmodule)
set(BOOST_DIR /home/dev/Projects/boost_1_85_0)

add_executable(${PNAME} main.cpp)


target_include_directories(${PNAME} PUBLIC ${BOOST_DIR})
target_include_directories(${PNAME} PUBLIC ./)

add_library(dslib STATIC dsClient.cpp dsServer.cpp dsClient.cpp)

target_include_directories(dslib PUBLIC ${BOOST_DIR})

target_link_libraries(${PNAME} dslib)


