cmake_minimum_required(VERSION 3.10)

project(scankeyb VERSION 1.0)

set (CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(EVDEV REQUIRED libevdev)
pkg_search_module(BLUEZ REQUIRED bluez)

include_directories(${EVDEV_INCLUDE_DIRS}
                    ${BLUEZ_INCLUDE_DIRS}
                    src/
                    headers/)

add_executable(main
               src/main.cpp
               src/keymap.cpp
               src/virtualkeyboard.cpp
               src/bluetoothrfcomm.cpp
               headers/keyboard_defines.h
               headers/keymap.h
               headers/virtualkeyboard.h
               headers/bluetoothrfcomm.h
               )

target_link_libraries(main
                      ${EVDEV_LIBRARIES}
                      ${BLUEZ_LIBRARIES})
