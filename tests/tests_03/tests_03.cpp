
//
// last modified: 29.06.26
//

//--


#include <chrono>
#include <numeric>
#include <utility>
#include <vector>

#include <nanoflann.hpp>
#include "nanoflann_utils.hpp"
#include "rep_kdtree_common.hpp"
#include "rep_kdtree_utils.hpp"


void generatePointCloudGrid(PointCloud<float>& pc,
                            const std::size_t& no_lon,
                            const std::size_t& no_lat) {

  const double lon_min = 0.0;
  const double lon_max = 360.0;
  const double lat_min = -90.0;
  const double lat_max = 90.0;

  const double dlon = (lon_max - lon_min) / no_lon;        // [0, 360)
  const double dlat = (lat_max - lat_min) / (no_lat - 1);  // [-90, 90]

  std::vector<std::pair<double, double>> grid;
  grid.reserve(no_lon * no_lat);

  for (std::size_t j = 0; j < no_lat; ++j) {
    double lat = lat_min + j * dlat;
    for (std::size_t i = 0; i < no_lon; ++i) {
      double lon = lon_min + i * dlon;
      grid.emplace_back(lon, lat);
    }
  }

  // number of locations
  auto no_locs = grid.size();

  pc.pts.resize(no_locs);
  for (std::size_t i = 0; i < no_locs; ++i){
    pc.pts[i].x = grid[i].first;
    pc.pts[i].y = grid[i].second;
  }
}


void test_01() {

  std::cout << "\n> test #01\n\nstarting ...\n" << std::endl;
  auto start = std::chrono::steady_clock::now();

  // dimensionality
  const int dim{2};
  
  // numbers of lon/lat
  const std::size_t no_lon {1280};
  const std::size_t no_lat {960};

  PointCloud<float> grid;

  // generating cloud points ...
  generatePointCloudGrid(grid, no_lon, no_lat);

  //displayPointCloud(grid, (no_lon * no_lat));

  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    PointCloud<float>,
    dim,
    uint32_t>;

  kdtree_index index(dim, grid, {10});

  // query point (reference point) in 2D space
  const float query_point[dim] = {33.75, -9.45};

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
        
  std::cout << "\n++ KNN search" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1]
            << "\nno. of nearest neighbors = " << no_nneighbors << std::endl;
  std::cout << "nearest neighbors [index; Long/Lat; squared distance]: " << std::endl;
  for (size_t i = 0; i < no_nneighbors; i++) {
    std::cout << idxs_nn[i] << "; "
              << grid.pts[idxs_nn[i]].x << ", "
              << grid.pts[idxs_nn[i]].y << "; "
              << dists_squared[i] << std::endl;
  }

  std::cout << "\n... done\n" << std::endl;
  auto end = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "elapsed time: " << elapsed.count() << " [ms]\n" << std::endl;

}


void test_02() {

  std::cout << "\n> test #02\n\nstarting ...\n" << std::endl;
  auto start = std::chrono::steady_clock::now();

  // dimensionality
  const int dim{2};
  
  // numbers of lon/lat
  const std::size_t no_lon {1280};
  const std::size_t no_lat {960};

  PointCloud<float> grid;

  // generating cloud points ...
  generatePointCloudGrid(grid, no_lon, no_lat);

  //displayPointCloud(grid, (no_lon * no_lat));

  using kdtree_index = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud<float>>,
    PointCloud<float>,
    dim,
    uint32_t>;

  kdtree_index index(dim, grid, {10});
  
  // query point (reference point) in 2D space
  const float query_point[dim] = {33.75, -9.45};
  
  // search radius
  const float search_radius {0.1};

  // carrying out a search within a ROI (within a search radius) ...

  // indeces of the points within the ROI and squared distances
  std::vector<nanoflann::ResultItem<uint32_t, float>> roi_specs;

  const size_t no_roi_points = index.radiusSearch(&query_point[0],
                                                  search_radius,
                                                  roi_specs);
  
        
  std::cout << "\n++ search within a ROI" << std::endl;
  std::cout << "query point (reference point): "
            << query_point[0] << ", " << query_point[1]
            << "\nno. of ROI points = " << no_roi_points << std::endl;
  std::cout << "ROI points [index; Long/Lat; squared distance]: " << std::endl;
  for (size_t i = 0; i < no_roi_points; i++) {
    std::cout << roi_specs[i].first << "; "
              << grid.pts[roi_specs[i].first].x << ", "
              << grid.pts[roi_specs[i].first].y << "; "
              << roi_specs[i].second << std::endl;
  }

  std::cout << "\n... done\n" << std::endl;
  auto end = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "elapsed time: " << elapsed.count() << " [ms]\n" << std::endl;

}


//--

int main(void)
{

  // battery of tests
  test_01();
  test_02();
  
  return(0);
}
