cmake_minimum_required(VERSION 3.14)
project(lmel)

set(CMAKE_CXX_STANDARD 17)

file(GLOB test_ls test/*.h)
file(GLOB lmel_ls lmel/*.h)

add_executable(${PROJECT_NAME} main.cpp ${lmel_ls} ${test_ls})
