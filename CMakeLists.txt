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
# all sources
message("CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")
FILE(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/*.h")
FILE(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/main.cpp")
SET(TARGET_SRC ${TARGET_CPP} ${TARGET_H})

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE)
target_link_libraries(${PROJECT_NAME} Qt5::Core ${GTEST_LIBRARIES} pthread)
