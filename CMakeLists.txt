cmake_minimum_required(VERSION 3.27.4)
project(CFGManager LANGUAGES CXX)



set(ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_CPP "${ROOT_FOLDER}/src/sources/CFGManager.cpp")
set(SOURCE_HEADER "${ROOT_FOLDER}/src/include/CFGManager.h")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT_FOLDER}/build/CFGManager/lib")
set(INCLUDE_OUTPUT_DIRECTORY "${ROOT_FOLDER}/build/CFGManager/include")


set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Release)


if(MSVC)
    add_definitions(-Wall -WX)
else()
    add_definitions(-Wall -Wpedantic -Wextra -Werror)
endif()



option(BUILD_TESTS "Need to build tests?" OFF)


# ========================================= MAKING BUILD DIRECTORY =========================================
make_directory(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
make_directory(${INCLUDE_OUTPUT_DIRECTORY})



# =========================================    BUILDING LIBRARY    =========================================
add_library(${CMAKE_PROJECT_NAME} ${SOURCE_CPP})



# =========================================     COPYING HEADERS    =========================================
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} COMMAND ${CMAKE_COMMAND} -E 
                    copy ${SOURCE_HEADER} ${INCLUDE_OUTPUT_DIRECTORY})



# =========================================     BUILDING TESTS     =========================================


if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${ROOT_FOLDER}/tests)
endif()
