cmake_minimum_required(VERSION 3.30)
project(distributed_group VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PNAME dsmodule_cli)
list(APPEND CMAKE_CXX_FLAGS "-O0 -g")
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Building for LINUX architecture...")
    set(BOOST_DIR /home/dev/commonlibs/boost_1_88_0)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "Building for APPLE architecture...")
    set(BOOST_DIR /Users/mtqdev/commonlibs/boost_1_88_0)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    message(STATUS "Compiling Error...")
endif ()

add_subdirectory(dsmodule_dir)

add_executable(${PNAME} main.cpp)
target_link_libraries(${PNAME} ds_module)


# $BOOST_DIR set on top CMakelists.txt
#target_include_directories(ds_module PUBLIC ${BOOST_DIR})

target_include_directories(${PNAME} PUBLIC dsmodule_dir/include)

install(TARGETS ${PNAME}
    RUNTIME DESTINATION bin)

if(NOT APPLE)
# ---- Doxygen ----
find_package(Doxygen REQUIRED)

set(DOXYGEN_IN  ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Gerando documentação com Doxygen..."
        VERBATIM
)

add_custom_target(docs ALL
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html
)

# Alvo para limpar docs (opcional)
add_custom_target(docs-clean
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_CURRENT_BINARY_DIR}/docs
        COMMENT "Limpando documentação..."
)

endif () #if NOT APPLE