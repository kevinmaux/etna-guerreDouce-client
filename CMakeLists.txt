cmake_minimum_required(VERSION 2.8)

project(guerreDouce)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )
find_package (Threads)

set(HEADERS
        src/clientZmq.h
        src/game.h
        src/notification.h
        iniReader/SimpleIni.h
        iniReader/ConvertUTF.h
	)

set(SOURCES
        src/main.cpp
        src/clientZmq.cpp
        src/game.cpp
        src/notification.cpp
        iniReader/ConvertUTF.c
        iniReader/snippets.cpp
	)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ZeroMQ_LIBRARY})
