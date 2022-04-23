# CMakeList.txt: проект CMake для Program_2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Program_2 "main.cpp" "Program_2.h" "server.hpp" "server.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
