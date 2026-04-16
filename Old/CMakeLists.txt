cmake_minimum_required(VERSION 3.20)
project(Test_3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Скорочує шляхи до об'єктних файлів
set(CMAKE_OBJECT_PATH_MAX 260)

# Вкажи де знаходяться заголовкові файли
include_directories(include)

# Шлях до SDL2 (змініть якщо у вас інший)
set(SDL2_PATH "D:/SDL2/SDL2-2.32.4")

include_directories(
    include
    ${SDL2_PATH}/include
)

link_directories(
    ${SDL2_PATH}/lib/x64
)

# Вкажи всі .cpp файли
add_executable(Test_3D
    src/main.cpp
    src/ObjParser.cpp
    src/Renderer.cpp
)

target_link_libraries(Test_3D
    SDL2
    SDL2main
)

# Копіювати OBJ файли після білду
add_custom_command(TARGET Test_3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/OBJ
    $<TARGET_FILE_DIR:Test_3D>/OBJ
)

# Копіювати SDL2.dll після білду
add_custom_command(TARGET Test_3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${SDL2_PATH}/lib/x64/SDL2.dll
    $<TARGET_FILE_DIR:Test_3D>
)