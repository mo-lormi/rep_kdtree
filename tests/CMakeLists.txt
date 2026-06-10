
#
# last modified: 01.06.26
#

#--

enable_testing()

add_subdirectory(tests_01)
add_subdirectory(tests_02)


#--

message(STATUS "")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "")

#--

#
# battery of tests
#

add_test(NAME    bt01
         COMMAND tests01)

add_test(NAME    bt02
         COMMAND tests02)
