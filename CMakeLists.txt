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

add_executable(${PROJECT_NAME} src/main.cpp src/AppWindow.h src/AppWindow.cpp src/util/file_helper.cpp src/util/file_helper.h src/util/NotImplementedYetException.h src/util/NotImplementedYetException.cpp src/util/models.h src/TextRenderer.cpp src/TextRenderer.h src/handler/EventHandler.h src/handler/InsertModeHandler.cpp src/handler/InsertModeHandler.cpp src/handler/NormalModeHandler.h src/handler/NormalModeHandler.cpp) 

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
