cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT SFMLGame)
set(SOURCES
        ../src/main.cpp)
set(HEADERS)

project(${PROJECT})

find_package(SFML
        COMPONENTS
        graphics
        audio
        REQUIRED)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} sfml-graphics sfml-audio)
