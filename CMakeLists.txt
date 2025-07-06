cmake_minimum_required(VERSION 3.31)
project(TableBuilder C)

set(CMAKE_C_STANDARD 23)

#add_library(TableBuilder STATIC library.c)
add_library(TableBuilder STATIC tableBuilder.c tblbld.h)
