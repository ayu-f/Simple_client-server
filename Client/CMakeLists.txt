# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("Program_1")
find_library(PTHREAD_LIBRARY pthread)

# Включите подпроекты.
add_subdirectory ("Program_1")
