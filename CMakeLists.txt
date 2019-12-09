cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0074 NEW)
set (CMAKE_CXX_STANDARD 11)
project(CppMeta)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

#set(BOOST_ROOT D:/Applications/boost_1_69_0)
#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
#set(Boost_USE_DEBUG_LIBS         ON) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

set(SOURCE main.cpp)


find_package(Boost REQUIRED COMPONENTS thread unit_test_framework test_exec_monitor)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_ROOT}/lib64-msvc-14.1)

message("${Boost_INCLUDE_DIRS}")
#message("${Boost_LIBRARIES}")

if(Boost_FOUND)
  add_executable(${PROJECT_NAME} ${SOURCE})
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
  #target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
endif()