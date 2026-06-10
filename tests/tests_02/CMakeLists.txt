
#
# last modified: 01.06.26
#

#--


add_executable(tests02
  tests_02.cpp)

target_sources(tests02 PUBLIC
  ${PROJECT_SOURCE_DIR}/src/rep_kdtree_utils.cpp)

target_include_directories(tests02 PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $ENV{NANOFLANN_INCLUDE_DIR})

target_link_libraries(tests02
  nanoflann::nanoflann)
