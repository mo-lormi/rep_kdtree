
#
# last modified: 28.05.26
#

#--

cmake_minimum_required(VERSION 3.26.0)


#--

project(rep_kdtree
        VERSION 1.0
        DESCRIPTION "kd-tree method, nanoflann library"
	LANGUAGES C CXX)

find_package(nanoflann)
      
add_subdirectory(src)
add_subdirectory(tests)


#--

enable_testing()
