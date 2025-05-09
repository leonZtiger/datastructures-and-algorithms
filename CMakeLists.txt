cmake_minimum_required(VERSION 3.10.0)
project(list VERSION 0.1.0 LANGUAGES C)

include_directories(include)
add_executable(list src/main.c src/load_file.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
