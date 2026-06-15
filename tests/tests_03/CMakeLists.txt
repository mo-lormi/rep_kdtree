
#
# last modified: 11.06.26
#

#--


add_executable(tests03
  tests_03.cpp)

target_sources(tests03 PUBLIC
  ${PROJECT_SOURCE_DIR}/src/rep_kdtree_utils.cpp)

target_include_directories(tests03 PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $ENV{NANOFLANN_INCLUDE_DIR})

target_link_libraries(tests03
  nanoflann::nanoflann)
