﻿# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

find_library(PTHREAD_LIBRARY pthread)
SET(CMAKE_CXX_FLAGS  "-pthread")
include_directories(include)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject1 "main.cpp"  "Reader.hpp" "Sender.hpp" "ThException.hpp" "Client.hpp" "Manager.hpp"  "Reader.cpp" "Sender.cpp")
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
