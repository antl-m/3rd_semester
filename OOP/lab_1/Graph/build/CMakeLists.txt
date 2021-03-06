cmake_minimum_required (VERSION 3.17)

set (PROJECT 
	Graph)

set (HEADERS 
	../Graph.h)

set (SOURCES
	../../sources/Bool.cpp)

set (TESTS_SOURCES
	../tests/MatrixGraphTests.cpp
	../tests/LinkedGraphTests.cpp
	../tests/runner.cpp)

project (${PROJECT})

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_library (${PROJECT} ${HEADERS} ${SOURCES})

if (TESTS_SOURCES)
	set (Boost_USE_STATIC_LIBS ON)
	set (Boost_USE_MULTITHREADED ON)
	find_package (Boost
			COMPONENTS
			unit_test_framework
			REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	set (TEST test_${PROJECT})
	add_executable (${TEST} ${TESTS_SOURCES})
	target_link_libraries (${TEST} ${PROJECT} ${Boost_LIBRARIES})
	set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
	enable_testing ()
	add_test (${TEST} ${TEST})
endif ()
