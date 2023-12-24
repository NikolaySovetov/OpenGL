cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(glad LANGUAGES C)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)

