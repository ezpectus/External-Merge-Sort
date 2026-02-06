# CMakeList.txt: проект CMake для External_MergeSort; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
cmake_minimum_required(VERSION 3.15)

project(External_MergeSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(External_MergeSort
    src/main.cpp
    src/generator.cpp
    src/split_sort.cpp
    src/merge.cpp
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
