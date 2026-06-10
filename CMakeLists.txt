
#
# last modified: 10.06.26
#

#--

cmake_minimum_required(VERSION 3.26.0)


#--

project(rep_kdtree
        VERSION 1.0
        DESCRIPTION "k-d tree method, a repository for tests, examples, and templates"
        LANGUAGES C CXX)

find_package(nanoflann)
      
add_subdirectory(src)
add_subdirectory(tests)


#--

enable_testing()
