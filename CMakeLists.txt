cmake_minimum_required(VERSION 3.17.3)
project(Psi)

set(CMAKE_CXX_STANDARD 17)

add_executable(Psi main.cpp Example/Ex1_Reference.h Example/Ex2_New_Delete.h Example/Ex3_Math.h Example/Ex4_String.h Example/BinarySearch.h Example/Ex5MyString.h)