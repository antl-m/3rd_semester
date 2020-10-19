cmake_minimum_required (VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

set (PROJECT test_proj)

set (HEADERS)

set (SOURCES
        main.cpp)

set (LIBRARIES)
#
#set (BOOST_COMPONENTS)
#
#set (Boost_USE_STATIC_LIBS ON)
#set (Boost_USE_DYN_LIBS ON)
#set (Boost_USE_MULTITHREADED ON)

project (${PROJECT})

#find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

if (MSVC)
    add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions (-Wall -pedantic)
else ()
    message ("Unknown compiler")
endif ()

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT} ${LIBRARIES} ${Boost_LIBRARIES} ws2_32)

enable_testing ()
