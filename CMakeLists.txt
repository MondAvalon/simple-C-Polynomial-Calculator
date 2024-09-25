cmake_minimum_required(VERSION 3.29)
project(CPolynomialCalculator C)

set(CMAKE_C_STANDARD 11)

add_executable(CPolynomialCalculator source/main.c
        source/Node.c
        source/Node.h
        # tests/test.c
)

