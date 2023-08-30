cmake_minimum_required(VERSION 3.12)
project(LoggerExample)

set(CMAKE_CXX_STANDARD 11)

# Boost dependencies
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS log log_setup)

# Add the Logger library
add_library(Logger STATIC lib/Logger.cpp)
add_library(ipc STATIC lib/message_queue_reader.cpp)
add_library(ipcS STATIC lib/message_queue_writer.cpp)
add_library(mathF STATIC lib/math_functions.cpp)

target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(Logger PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(ipc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(ipcS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(mathF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)


target_link_libraries(Logger PUBLIC Threads::Threads)
target_link_libraries(Logger PUBLIC Boost::log_setup Boost::log)


# Create the executable
add_executable(logger logger.cpp)
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(logger PUBLIC ${Boost_INCLUDE_DIRS})

add_executable(mathM math.cpp)
target_include_directories(mathM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mathM PUBLIC ipcS)
target_link_libraries(mathM PUBLIC mathF)


# Link pthread library

target_link_libraries(logger PUBLIC Logger)
target_link_libraries(logger PUBLIC ipc)
target_compile_options(logger PRIVATE -g)



