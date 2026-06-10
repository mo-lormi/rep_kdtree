
#
# last modified: 28.05.26
#

#--

configure_file(rep_kdtree_config.hpp.in rep_kdtree_config.hpp)


#--

install(FILES ${PROJECT_BINARY_DIR}/src/rep_kdtree_config.hpp DESTINATION ${PROJECT_SOURCE_DIR}/include)
