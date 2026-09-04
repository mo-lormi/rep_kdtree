
#
# last modified: 04.09.26
#

#--


add_executable(tests02
  tests_02.cpp)

target_sources(tests02 PRIVATE
  ${PROJECT_SOURCE_DIR}/src/rep_kdtree_utils.cpp)

target_include_directories(tests02 PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  $ENV{NANOFLANN_INCLUDE_DIR})

target_link_libraries(tests02
  nanoflann::nanoflann)
