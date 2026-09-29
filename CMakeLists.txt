cmake_minimum_required(VERSION 3.14)
project(TriangleCenter)

# Генерируем файл для автодополнения кода
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Подключаем модуль для скачивания из сети
include(FetchContent)

# Отключаем сборку аудио и сети, чтобы SFML скомпилировался в 2 раза быстрее
# (для расчета площади они не нужны)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
# Собираем как статические библиотеки, чтобы не таскать за собой .dll файлы
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

message(STATUS "Скачиваем SFML 3 с GitHub...")

# Указываем, откуда качать
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.1.0   # Версия (можно поменять на 3.0.2)
        GIT_SHALLOW    ON      # Скачивать без истории коммитов (намного быстрее)
)

# Скачиваем и добавляем в проект
FetchContent_MakeAvailable(SFML)

# Указываем ваш файл с исходным кодом
add_executable(${PROJECT_NAME} main.cpp)

# Линкуем SFML с проектом (В версии 3 модули пишутся с заглавной буквы)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)