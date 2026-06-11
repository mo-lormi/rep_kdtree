
//
// last modified: 09.06.26
//

//--


#include <vector>

#include <nanoflann.hpp>
#include "nanoflann_utils.hpp"
#include "rep_kdtree_common.hpp"
#include "rep_kdtree_utils.hpp"


void generatePointCloud_01(PointCloud<float>& pc, const size_t no_cpoints) {
  pc.pts.resize(no_cpoints);

   /*
   0:{10,10}   1:{20,10}   2:{30,10}
   3:{10,0}    4:{20,0}    5:{30,0}
   6:{10,-10}  7:{20,-10}  8:{30,-10}
  */

  pc.pts[0].x = 10.0;
  pc.pts[0].y = 10.0;
  pc.pts[1].x = 20.0;
  pc.pts[1].y = 10.0;
  pc.pts[2].x = 30.0;
  pc.pts[2].y = 10.0;
  pc.pts[3].x = 10.0;
  pc.pts[3].y = 0.0;
  pc.pts[4].x = 20.0;
  pc.pts[4].y = 0.0;
  pc.pts[5].x = 30.0;
  pc.pts[5].y = 0.0;
  pc.pts[6].x = 10.0;
  pc.pts[6].y = -10.0;
  pc.pts[7].x = 20.0;
  pc.pts[7].y = -10.0;
  pc.pts[8].x = 30.0;
  pc.pts[8].y = -10.0;
}


void generatePointCloud_02(PointCloud<float>& pc, const size_t no_cpoints) {
  pc.pts.resize(no_cpoints);

  /*
   0:{45,90}   1:{90,90}   2:{135,90}
   3:{45,30}   4:{90,30}   5:{135,30}
   6:{45,-30}  7:{90,-30}  8:{135,-30}
  */

  pc.pts[0].x = 45.0;
  pc.pts[0].y = 90.0;
  pc.pts[1].x = 90.0;
  pc.pts[1].y = 90.0;
  pc.pts[2].x = 135.0;
  pc.pts[2].y = 90.0;
  pc.pts[3].x = 45.0;
  pc.pts[3].y = 30.0;
  pc.pts[4].x = 90.0;
  pc.pts[4].y = 30.0;
  pc.pts[5].x = 135.0;
  pc.pts[5].y = 30.0;
  pc.pts[6].x = 45.0;
  pc.pts[6].y = -30.0;
  pc.pts[7].x = 90.0;
  pc.pts[7].y = -30.0;
  pc.pts[8].x = 135.0;
  pc.pts[8].y = -30.0;
}


void test_01() {

  std::cout << "\n> test #01\n" << std::endl;

  // dimensionality
  const int dim{2};
  
  // query point (reference point) in 2D space
  float query_point[dim] = {15.0, 0.0};

  const size_t no_points{9};

  PointCloud<float> cloud;

  // generating cloud points ...
  generatePointCloud_01(cloud, no_points);

  displayPointCloud(cloud, 9);

  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    PointCloud<float>,
    dim,
    size_t>;

  kdtree_index index(dim, cloud, {10});

  // carrying out a KNN search ...

  // number of nearest neighbors that are requested/considered
  const size_t no_nneighbors = 1;
  // index of the nearest neighbor
  size_t idx_nn;
  // squared distance
  float dist_squared;
  
  nanoflann::KNNResultSet<float> resultSet(no_nneighbors);
  resultSet.init(&idx_nn, &dist_squared);
  index.findNeighbors(resultSet, &query_point[0]);

  std::cout << "\n[KNN search]" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1]
            << "\nno. of nearest neighbors = " << no_nneighbors
            << "\nindex of the nearest neighbor = " << idx_nn
            << "\nsquared distance = " << dist_squared << "\n" << std::endl;
}


void test_02() {

  std::cout << "\n> test #02\n" << std::endl;

  // dimensionality
  const int dim{2};
  
  // query point (reference point) in 2D space
  float query_point[dim] = {90.0, 0.0};

  const size_t no_points{9};

  PointCloud<float> cloud;

  // generating cloud points ...
  generatePointCloud_02(cloud, no_points);

  displayPointCloud(cloud, 9);

  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    PointCloud<float>,
    dim,
    size_t>;

  kdtree_index index(dim, cloud, {10});

  // carrying out a KNN search ...

  // number of nearest neighbors that are requested/considered
  const size_t no_nneighbors = 1;
  // index of the nearest neighbor
  size_t idx_nn;
  // squared distance
  float dist_squared;
  
  nanoflann::KNNResultSet<float> resultSet(no_nneighbors);
  resultSet.init(&idx_nn, &dist_squared);
  index.findNeighbors(resultSet, &query_point[0]);

  std::cout << "\n[KNN search]" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1]
            << "\nno. of nearest neighbors = " << no_nneighbors
            << "\nindex of the nearest neighbor = " << idx_nn
            << "\nsquared distance = " << dist_squared << "\n" << std::endl;
}


void test_03() {

  std::cout << "\n> test #03\n" << std::endl;

  // dimensionality
  const int dim{2};
  
  // query point (reference point) in 2D space
  const float query_point[dim] = {90.0, 0.0};

  const size_t no_points{9};

  PointCloud<float> cloud;

  // generating cloud points ...
  generatePointCloud_02(cloud, no_points);

  displayPointCloud(cloud, 9);

  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    PointCloud<float>,
    dim,
    uint32_t>;

  kdtree_index index(dim, cloud, {10});

  // carrying out a KNN search ...

  // number of nearest neighbors that are requested/considered
  size_t no_nneighbors = 4;
  // indeces of the nearest neighbors
  std::vector<uint32_t> idxs_nn(no_nneighbors);
  // squared distances
  std::vector<float> dists_squared(no_nneighbors);
  
  no_nneighbors = index.knnSearch(&query_point[0],
                                  no_nneighbors,
                                  &idxs_nn[0],
                                  &dists_squared[0]);

  idxs_nn.resize(no_nneighbors);
  dists_squared.resize(no_nneighbors);
        
  std::cout << "\n[KNN search]" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1]
            << "\nno. of nearest neighbors = " << no_nneighbors << std::endl;
  std::cout << "indeces of the nearest neighbor and squared distances = " << std::endl;
  for (size_t i = 0; i < no_nneighbors; i++) {
    std::cout << idxs_nn[i] << ", " << dists_squared[i] << std::endl;
  }
  
}


//--

int main(void)
{

  // battery of tests
  test_01();
  test_02();
  test_03();
  
  return(0);
}
