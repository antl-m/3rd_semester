cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT SFMLGame)
set(SOURCES
        ../src/main.cpp
        ../src/MainSceneWindow/MainSceneWindow.cpp
        ../src/Player/Player.cpp ../src/Utility/Utility.cpp ../src/Utility/Utility.h ../src/Wall/Wall.cpp ../src/Wall/Wall.h ../src/AI/AI.cpp ../src/AI/AI.h)
set(HEADERS
        ../src/MainSceneWindow/MainSceneWindow.h
        ../src/Player/Player.h ../src/Colors/Colors.h ../src/Utility/Utility.cpp ../src/Utility/Utility.h ../src/Wall/Wall.cpp ../src/Wall/Wall.h ../src/AI/AI.cpp ../src/AI/AI.h)

project(${PROJECT})

find_package(SFML
        COMPONENTS
        graphics
        REQUIRED)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} sfml-graphics sfml-audio)
