cmake_minimum_required(VERSION 3.16)
project(UDRMS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Console executable ─────────────────────────────────────────────────────────
set(SOURCES
    src/Student.cpp
    src/Menu.cpp
    src/Restaurant.cpp
    src/Room.cpp
    src/Dormitory.cpp
    src/University.cpp
    src/main.cpp
)

add_executable(UDRMS ${SOURCES})
target_include_directories(UDRMS PRIVATE include)

# ── Qt GUI executable (optional — comment out if Qt is unavailable) ────────────
find_package(Qt6 COMPONENTS Widgets QUIET)
if (Qt6_FOUND)
    message(STATUS "Qt6 found — building GUI")
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    set(GUI_SOURCES
        src/Student.cpp
        src/Menu.cpp
        src/Restaurant.cpp
        src/Room.cpp
        src/Dormitory.cpp
        src/University.cpp
        ui/MainWindow.cpp
        ui/main_gui.cpp
    )

    add_executable(UDRMS_GUI ${GUI_SOURCES})
    target_include_directories(UDRMS_GUI PRIVATE include ui)
    target_link_libraries(UDRMS_GUI PRIVATE Qt6::Widgets)
else()
    message(STATUS "Qt6 not found — skipping GUI build")
endif()
