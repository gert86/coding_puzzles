cmake_minimum_required(VERSION 2.8.12)

project(interview_question_roman_numbers)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

# main source
set(SOURCES "main.cpp")

# lib sources
set(LIBSOURCES ${LIBSOURCES} "../common/stack.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/stack.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/queue.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/queue.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/linkedlist.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/linkedlist.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/doublylinkedlist.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/doublylinkedlist.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/doublylinkedlistderived.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/doublylinkedlistderived.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/binarytree.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/binarytree.cpp")  # enable if implementation is moved to cpp

set(LIBSOURCES ${LIBSOURCES} "../common/graph.h")
#set(LIBSOURCES ${LIBSOURCES} "../common/graph.cpp")  # enable if implementation is moved to cpp

# lib
add_library(mylib ${LIBSOURCES} )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ../common)
target_link_libraries(${PROJECT_NAME} Qt5::Core mylib)
