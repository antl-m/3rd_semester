cmake_minimum_required (VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set (PROJECT 
	module1_task1)

set (HEADERS
		../User.h
		../Theme.h
		../Post.h
		../Server.h)

set (SOURCES
		../User.cpp
		../Theme.cpp
		../Post.cpp
		../Server.cpp)

set (TESTS_SOURCES
		../tests/test_main.cpp
		../tests/test_file.cpp)

project (${PROJECT})

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

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
	set_target_properties(${TEST} PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries (${TEST} ${Boost_LIBRARIES})
	enable_testing ()
	add_test (${TEST} ${TEST})
endif()
add_executable (${PROJECT} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
