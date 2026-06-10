
//
// last modified: 29.05.26
//

//--

#ifndef REP_KDTREE_UTILS_H
#define REP_KDTREE_UTILS_H


#include <vector>

#include "rep_kdtree_common.hpp"
#include "nanoflann_utils.hpp"


void initRandomNumberGen();


template <typename T>
void displayPointCloud(PointCloud<T>& pc, const size_t no_cpoints) {

  try {
    if (no_cpoints > pc.kdtree_get_point_count()) {
      throw std::invalid_argument(
        "value must be less than or equal the number of cloud points");
    }
  } catch (const std::exception& e) {
    std::cerr << "> ERROR: " << e.what() << '\n';
    std::terminate();
  }

  for (size_t i = 0; i < no_cpoints; i++) {
    std::cout << "index: " << i
	      << "; " << pc.pts[i].x
	      << ", " << pc.pts[i].y
	      << ", " << pc.pts[i].z << std::endl;
  }
}


#endif /* REP_KDTREE_UTILS_H */
