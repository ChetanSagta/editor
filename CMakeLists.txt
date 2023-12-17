cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra -Werror -Wshadow")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(editor)
# Search pkg-config utility first
find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED COMPONENTS SDL2::TTF)
find_package(spdlog REQUIRED)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/appwindow.h
    src/appwindow.cpp
    src/handler/eventhandler.h
    src/handler/eventhandler.cpp
    src/handler/insertmodehandler.cpp
    src/handler/insertmodehandler.cpp
    src/handler/normalmodehandler.h
    src/handler/normalmodehandler.cpp
    src/render/cursor.h
    src/render/cursor.cpp
    src/render/line.h
    src/render/line.cpp
    src/render/textrenderer.cpp
    src/render/textrenderer.h
    src/util/file_helper.cpp
    src/util/file_helper.h
    src/util/fontmanager.h
    src/util/fontmanager.cpp
    src/util/notimplementedyetexception.h
    src/util/notimplementedyetexception.cpp
    src/util/models.h)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
