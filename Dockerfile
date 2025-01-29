# Используем базовый образ Ubuntu 20.04
FROM ubuntu:20.04

# Устанавливаем необходимые пакеты и зависимости
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    tzdata \
    build-essential \
    cmake \
    g++ \
    libssl-dev \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем часовой пояс
ARG TIMEZONE="Europe/Moscow"  # Замените на ваш часовой пояс
ENV TZ=${TIMEZONE}
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Создаем рабочую директорию внутри контейнера
WORKDIR /project

# Копируем файлы CMakeLists.txt и все остальные файлы проекта в контейнер
COPY CMakeLists.txt /project/
COPY src /project/src
COPY lib /project/lib

# Если вы хотите использовать уже собранный бинарник, просто скопируйте его
COPY build/DPAPI /project/build/

# Если нужно собрать проект заново, используйте следующие команды:
# RUN mkdir -p build && cd build && \
#     cmake .. && \
#     make

# Указываем команду для запуска приложения
CMD ["./build/DPAPI"]
