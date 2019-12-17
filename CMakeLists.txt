cmake_minimum_required(VERSION 3.15)
project(perMonitor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CFLAGS "${CMAKE_C_FLAGS} -pthread -lcurl")

add_executable(perMonitor main.c miner/cpu.h miner/disk.h miner/mem.h miner/net.h queue/q.h posting/http.c posting/http.h posting/json.c posting/json.h)
target_link_libraries(perMonitor curl)