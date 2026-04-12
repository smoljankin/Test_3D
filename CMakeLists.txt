cmake_minimum_required(VERSION 3.20)
project(Test_3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вкажи де знаходяться заголовкові файли
include_directories(include)

# Вкажи всі .cpp файли
add_executable(Test_3D
    src/main.cpp
    src/ObjParser.cpp
)