
//
// last modified: 01.06.26
//

//--


#include <nanoflann.hpp>
#include "nanoflann_utils.hpp"
#include "rep_kdtree_common.hpp"
#include "rep_kdtree_utils.hpp"


void test_01() {

  std::cout << "\n> test #01\n" << std::endl;

  const size_t no_points{5};

  PointCloud<float> cloud;

  // generating cloud points ...
  initRandomNumberGen();
  generateRandomPointCloud(cloud, no_points);

  auto no_cloud_points = cloud.kdtree_get_point_count();

  std::cout << "no. of cloud points: " << no_cloud_points << std::endl;

  displayPointCloud(cloud, 5);

}


void test_02() {

  std::cout << "\n> test #02\n" << std::endl;

  // dimensionality
  const int dim{3};
  
  // query point (reference point) in 3D space
  float query_point[dim] = {0.5, 0.5, 0.5};

  const size_t no_points{5};

  PointCloud<float> cloud;

  // generating cloud points ...
  initRandomNumberGen();
  generateRandomPointCloud(cloud, no_points);

  displayPointCloud(cloud, 5);

  // kd-tree index
  // (it contains the k-d trees and other information for indexing
  // a set of points for nearest-neighbor matching)
  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    // Distance
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    // DatasetAdaptor
    PointCloud<float>,
    // Dim (dimensionality)
    dim,
    // IndexType
    size_t>;

  kdtree_index index(dim, cloud, {10});

  // carrying out a KNN search ...

  // number of nearest neighbors that are requested/considered
  const size_t no_nneighbors = 1;
  // index of the nearest neighbo
  size_t idx_nn;
  // squared distance
  float dist_squared;
  
  nanoflann::KNNResultSet<float> resultSet(no_nneighbors);
  resultSet.init(&idx_nn, &dist_squared);
  index.findNeighbors(resultSet, &query_point[0]);

  std::cout << "\n[KNN search]" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1] << ", " << query_point[2]
            << "\nno. of nearest neighbors = " << no_nneighbors
            << "\nindex of the nearest neighbor = " << idx_nn
            << "\nsquared distance = " << dist_squared << "\n" << std::endl;

}


//--

int main(void)
{

  // battery of tests
  test_01();
  test_02();
  
  return(0);
}
