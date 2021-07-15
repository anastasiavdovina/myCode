cmake_minimum_required(VERSION 3.17)
project(A3)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "boost_1_75_0")
set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(A3 base-types.hpp circle.hpp shape.hpp rectangle.hpp circle.cpp composite-shape.cpp composite-shape.hpp rectangle.cpp test-main.cpp test-rectangle.cpp test-composite-shape.cpp test-circle.cpp)