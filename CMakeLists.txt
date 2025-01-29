cmake_minimum_required(VERSION 3.8)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Создаем проект с именем DormandPrinceAPI
project(DPAPI)

# Определяем пути к заголовочным файлам
include_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/lib/nlohmann
)

# Создаем библиотеку DornandPrinceLib из исходных файлов в директории src
add_library(DornandPrinceLib STATIC 
    src/DormandPrince.cpp
)

# Создаем исполняемый файл DormandPrinceAPI из исходных файлов в директории src
add_executable(DPAPI 
    src/main.cpp
)

# Связываем библиотеку DornandPrinceLib с исполняемым файлом
target_link_libraries(DPAPI
    PRIVATE DornandPrinceLib
)
