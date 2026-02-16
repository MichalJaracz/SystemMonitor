# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(MojProjekt CXX)

# Tworzenie pliku wykonywalnego (podaj wszystkie pliki .cpp)
add_executable(Aplikacja 
    src/main.cpp 
    src/WindowsMonitor.cpp 
)

# Poinformowanie CMake, gdzie znajdują się pliki nagłówkowe (.h)
target_include_directories(Aplikacja PRIVATE ${CMAKE_SOURCE_DIR}/include)