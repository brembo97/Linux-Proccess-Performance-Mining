cmake_minimum_required(VERSION 3.15)
project(perMonitor C)

set(CMAKE_C_STANDARD 11)

add_executable(perMonitor main.c miner/cpu.h miner/disk.h miner/mem.h miner/net.h queue/q.h)
