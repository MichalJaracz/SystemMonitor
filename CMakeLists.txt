# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(SystemMonitor)

# Ustawiamy standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Szukamy bibliotek graficznych
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Tworzenie pliku wykonywalnego (podaj wszystkie pliki .cpp)
set(SOURCES
    src/main.cpp
    src/WindowsMonitor.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
)

# Tworzymy plik wykonywalny .exe
add_executable(Aplikacja ${SOURCES})

# Poinformowanie CMake, gdzie znajdują się pliki nagłówkowe (.h)
target_include_directories(Aplikacja PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/imgui
)

# Łączymy program z bibliotekami systemowymi i graficznymi
target_link_libraries(Aplikacja PRIVATE glfw OpenGL::GL)