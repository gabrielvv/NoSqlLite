cmake_minimum_required(VERSION 3.3)
project(NoSqlLite)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cli.c
    cli.h
    hashmap.c
    hashmap.h
    json.c
    json.h
    main.c
    nosql.c
    nosql.h)

add_executable(NoSqlLite ${SOURCE_FILES})