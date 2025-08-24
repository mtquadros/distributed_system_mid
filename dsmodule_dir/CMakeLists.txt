add_library(ds_module STATIC)

# Language requirement for clients
target_compile_features(ds_module PUBLIC cxx_std_20)

target_sources(ds_module PUBLIC src/dsClient.cpp
                                src/dsServer.cpp
                                src/manageTable.cpp
                                src/heartBeat.cpp
)

set_target_properties(ds_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY dsmodule_dir/lib
)
set_target_properties(ds_module PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

# $BOOST_DIR set on top CMakelists.txt
target_include_directories(ds_module
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${BOOST_DIR}
)


# Library .so version
