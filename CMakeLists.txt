cmake_minimum_required(VERSION 3.17.3)
project(Psi)

set(CMAKE_CXX_STANDARD 17)
if (WIN32)
    set(CMAKE_CXX_FLAGS "-fexec-charset=CP949")
endif()

add_executable(
        Psi
        main.cpp
        Example/ex1-reference.h
        Example/ex2-new-delete.h
        Example/ex3-math.h
        Example/ex4-string.h
        Example/binarySearch.h
        Example/ex5-string.h
        Example/ex6-complex.h Example/ex7-array.h Example/ex8-excel.h)
