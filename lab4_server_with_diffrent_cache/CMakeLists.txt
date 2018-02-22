cmake_minimum_required(VERSION 3.9)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab3
        httpreq.cc
        httpreq.hpp
        httpresp.cc
        httpresp.hpp
        main.cpp
        md5.cpp
        md5.h
        ThreadPoolServer.cpp
        ThreadSafeKVStoreLRU.cpp
        ThreadSafeListenerQueue.cpp)
