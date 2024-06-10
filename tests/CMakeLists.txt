cmake_minimum_required(VERSION 3.27.4)

project(main_test)



link_libraries(gtest ${CMAKE_PROJECT_NAME})
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})



set(ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES ${ROOT_FOLDER}/src/test.cpp)


set(EXECUTABLE_OUTPUT_PATH ${ROOT_FOLDER}/build/)
make_directory(${ROOT_FOLDER}/build/)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})



# ============================================== TESTING ==============================================

set(TESTS_DATA_DIRECTORY "${ROOT_FOLDER}/data")
configure_file("${ROOT_FOLDER}/src/cmake_defined_data_directory.h.in" 
               "${ROOT_FOLDER}/src/cmake_defined_data_directory.h" @ONLY)


add_test(NAME main_test COMMAND ${PROJECT_NAME})
