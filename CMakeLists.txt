cmake_minimum_required(VERSION 3.27)
project(CFGManager)


set(HEADER_PATH "src/include/CFGManager.h")
set(SOURCE_PATH "src/sources/CFGManager.cpp")
set(BUILD_DIR "build")


make_directory("${BUILD_DIR}/lib")
make_directory("${BUILD_DIR}/include")


set(CMAKE_CXX_FLAGS "-Wpedantic -Wall -Werror -std=c++23")



set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}/lib")
add_library(${PROJECT_NAME} STATIC ${SOURCE_PATH})


# =================================== COPYING HEADER FILE ===================================
add_custom_command(TARGET ${PROJECT_NAME}
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${HEADER_PATH} "${BUILD_DIR}/include")