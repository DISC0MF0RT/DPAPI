# Используем базовый образ для C++
FROM ubuntu:20.04

# Устанавливаем зависимости
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y g++ cmake libssl-dev wget tzdata

# Устанавливаем временную зону
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Копируем исходные файлы
COPY lib /DPAPI/lib
COPY src /DPAPI/src

# Устанавливаем рабочую директорию
WORKDIR /DPAPI

# Компиляция проекта с флагом -pthread
RUN g++ -o dpapi src/main.cpp src/DormandPrince.cpp -Ilib -std=c++17 -pthread

# Команда по умолчанию для запуска приложения
CMD ["./dpapi"]

