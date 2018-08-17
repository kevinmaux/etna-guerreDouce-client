cmake_minimum_required(VERSION 2.8)

project(guerreDouce)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libzmq)

set(HEADERS

	)

set(SOURCES
	main.cpp
	)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libzmq/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/libzmq/lib/libzmq.so)
