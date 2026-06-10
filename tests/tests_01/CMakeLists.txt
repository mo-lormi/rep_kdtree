
#
# last modified: 29.05.26
#

#--


add_executable(tests01
  tests_01.cpp)

target_sources(tests01 PUBLIC
  ${PROJECT_SOURCE_DIR}/src/rep_kdtree_utils.cpp)

target_include_directories(tests01 PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $ENV{NANOFLANN_INCLUDE_DIR})

target_link_libraries(tests01
  nanoflann::nanoflann)
