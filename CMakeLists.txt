cmake_minimum_required(VERSION 3.6)
project(netlicensing)

option(BUILD_SHARED_LIBS "Compile Shared Netlicensing-Client " FALSE)
set (BUILD_TESTS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenSSL REQUIRED)

set(NETLICENSE_CURL_DIR "" CACHE PATH "path to custom curl distro required by Netlicensing-cpp")
if(NETLICENSE_CURL_DIR)
    list(APPEND CMAKE_PREFIX_PATH "${NETLICENSE_CURL_DIR}")
endif()

find_package(CURL REQUIRED)

if (BUILD_TESTS)
	set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost 1.40 REQUIRED unit_test_framework)    
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

set(LIBS ${LIBS} ${CURL_LIBRARIES} ${JSONCPP_LIBRARIES})

add_definitions(-DCURL_STATICLIB)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

# enumerate header and source files for library
file(GLOB headers include/netlicensing/*.h)
source_group(include FILES ${headers})
file(GLOB sources src/*.cc)


# ------------------------------------------------------------------------------------#
# Set RPATH of installed targets to lib directory in installation folder
# ------------------------------------------------------------------------------------#
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")


add_library(netlicensing ${headers} ${sources})
target_link_libraries(netlicensing ${LIBS})

target_link_libraries(netlicensing CURL::libcurl)

# Install target
#
# On Windows, redist dll libraries have to be installed in the binary directory.
if (WIN32)
    install(TARGETS netlicensing ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
else()
    install(TARGETS netlicensing DESTINATION lib)
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/netlicensing" DESTINATION include)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/json" DESTINATION include)

# demo client 
file(GLOB client_demo_headers client_demo/${db2lp_component}/*h)
file(GLOB client_demo_sources client_demo/${db2lp_component}/*cc)
add_executable(netlicensing-client-demo ${client_demo_headers} ${client_demo_sources} )
target_link_libraries(netlicensing-client-demo netlicensing ${LIBS})

install(TARGETS netlicensing-client-demo DESTINATION bin)

if (BUILD_TESTS)
    include_directories(${Boost_INCLUDE_DIR} )
    link_directories(${Boost_LIBRARY_DIRS})
    set(test_dir "${PROJECT_SOURCE_DIR}/tests")
    file(GLOB_RECURSE test_headers ${test_dir}/*h)
    file(GLOB_RECURSE test_sources ${test_dir}/*cc)
    add_executable(run_tests ${headers} ${test_headers} ${test_sources})
    set_target_properties(run_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${test_dir})
    target_link_libraries(run_tests netlicensing ${LIBS})
    TARGET_LINK_LIBRARIES(run_tests ${Boost_LIBRARIES})
endif()





