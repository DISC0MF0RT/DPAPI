cmake_minimum_required(VERSION 3.14)
project(MyApiProject VERSION 1.0 LANGUAGES CXX)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавить include директорию
include_directories(${CMAKE_SOURCE_DIR}/include)

# Указать источник проекта
file(GLOB SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/include/*.h
)

# Создать исполняемый файл
add_executable(MyApiExecutable ${SOURCES})

# Указать флаги компиляции (если нужно)
target_compile_options(MyApiExecutable PRIVATE -Wall -Wextra -O2)

# Подключение сторонних библиотек
target_include_directories(MyApiExecutable PRIVATE src/include/nlohmann)
