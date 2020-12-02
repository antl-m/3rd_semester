cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT SFMLGame)
set(SOURCES
        ../src/main.cpp
        ../src/MainSceneWindow/MainSceneWindow.cpp
        ../src/Player/Player.cpp
        ../src/Utility/Utility.cpp
        ../src/Wall/Wall.cpp
        ../src/AI/AI.cpp)
set(HEADERS
        ../src/MainSceneWindow/MainSceneWindow.h
        ../src/Player/Player.h
        ../src/Colors/Colors.h
        ../src/Utility/Utility.h
        ../src/Wall/Wall.h
        ../src/AI/AI.h
        ../src/Graph/Graph.h)

project(${PROJECT})

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML
        COMPONENTS
        graphics
        main
        REQUIRED)


add_executable(${PROJECT} WIN32 ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfml-graphics sfml-main)
