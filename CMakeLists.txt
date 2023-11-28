cmake_minimum_required(VERSION 3.22.1)
# set(CMAKE_C_COMPILER gcc)
# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra -Werror -Wshadow")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(editor)
# Search pkg-config utility first
find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED COMPONENTS SDL2::TTF)
find_package(spdlog REQUIRED)

# Then use pkg-config for locate specific package

add_executable(${PROJECT_NAME} src/main.cpp src/AppWindow.h src/AppWindow.cpp src/util/file_helper.cpp src/util/file_helper.h src/util/NotImplementedYetException.h src/util/NotImplementedYetException.cpp) 
# Link with the IMPORTED target created by 'pkg_check_modules'
# That target contains both include directories and actual libraries for link.
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
