cmake_minimum_required(VERSION 3.28)
project(UBN_Addition C)

set(CMAKE_C_STANDARD 17)

add_executable(UBN_Addition main.c
        UBigNumber.h
        UBigNumber.c)
