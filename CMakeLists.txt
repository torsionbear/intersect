cmake_minimum_required(VERSION 3.6.0)

project(intersect)

add_subdirectory(test/googletest/built)

add_executable(intersect main.cpp intersect.cpp intersectTest.cpp)

target_link_libraries(intersect PRIVATE gtestd)