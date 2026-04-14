cmake_minimum_required(VERSION 3.20)
project(Test_3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Скорочує шляхи до об'єктних файлів
set(CMAKE_OBJECT_PATH_MAX 260)

# Вкажи де знаходяться заголовкові файли
include_directories(include)

# Вкажи всі .cpp файли
add_executable(Test_3D
    src/main.cpp
    src/ObjParser.cpp
)

add_custom_command(TARGET Test_3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/OBJ
    $<TARGET_FILE_DIR:Test_3D>/OBJ
)