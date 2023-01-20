cmake_minimum_required(VERSION 3.1)

project(coding_puzzles)

# C++14 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#set(GTEST_INCLUDE_DIRS "/home/gert/.conan/data/gtest/1.11.0/_/_/package/8887312d8d5d906d59a60762be586000713d5f48/include/gtest")
#set(GTEST_LIBRARIES "/home/gert/.conan/data/gtest/1.11.0/_/_/package/8887312d8d5d906d59a60762be586000713d5f48/lib/libgtestd.a")

# all sources
message("CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")
FILE(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/*.h")
FILE(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/main.cpp")
FILE(GLOB TARGET_CPP2 "${CMAKE_SOURCE_DIR}/other/ball_game/*.cpp")
SET(TARGET_SRC ${TARGET_CPP} ${TARGET_CPP2} ${TARGET_H})

add_executable(${PROJECT_NAME} ${TARGET_SRC} ${TARGET_CPP2})
target_include_directories(${PROJECT_NAME} PRIVATE)
target_link_libraries(${PROJECT_NAME} Qt5::Core ${GTEST_LIBRARIES} pthread)
