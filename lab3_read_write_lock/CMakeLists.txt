cmake_minimum_required(VERSION 3.8)
project(multicore_lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        httpreq.cc
        httpreq.hpp
        httpresp.cc
        httpresp.hpp
        main.cpp
        md5.cpp
        md5.h
        ThreadPoolServer.cpp
        ThreadSafeKVStore.cpp
        ThreadSafeListenerQueue.cpp)

add_executable(multicore_lab2 ${SOURCE_FILES})