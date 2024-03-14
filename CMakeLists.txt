cmake_minimum_required(VERSION 3.24)
project(iperf_test)
include_directories(".")
set(SOURCE_FILES 
    main.cpp 
    Analyzer.cpp
    Client.cpp
    Server.cpp
    Analyzer.h
    Client.h
    Server.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})