cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(DPAPI)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Указываем, где искать заголовочные файлы
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Добавляем исходные файлы
set(SOURCE_FILES
    src/DormandPrince.cpp
    src/main.cpp
    src/DormandPrince.h
)

# Указываем компиляцию исполнимого файла
add_executable(DPAPI ${SOURCE_FILES})

# Настроим линковку с библиотеками (если необходимо)
# target_link_libraries(DormandPrinceProject <libraries>)