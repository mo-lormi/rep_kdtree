/***********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright 2011-2025 Jose Luis Blanco (joseluisblancoc@gmail.com).
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

//
// last modified: 28.05.26
//

//--

#ifndef NANOFLANN_UTILS_H
#define NANOFLANN_UTILS_H


#include <vector>

#include "rep_kdtree_common.hpp"


//
// data structure defined in ...
// https://github.com/jlblancoc/nanoflann/blob/master/examples/utils.h
//
template <typename T>
struct PointCloud {

  struct Point {
    T x, y, z;
  };

  std::vector<Point> pts;

  // member function to get the number of data points
  inline size_t kdtree_get_point_count() const { return pts.size(); }

  // member function to get the dim'th component of the idx'th point in the class;
  // note that since this is inlined and the 'dim' argument is typically an
  // immediate value, the 'if/else' are actually solved at compile time
  inline T kdtree_get_pt(const size_t idx, const size_t dim) const {
    if (dim == 0)
      return pts[idx].x;
    else if (dim == 1)
      return pts[idx].y;
    else
      return pts[idx].z;
  }

  // Optional bounding-box computation: return false to default to a standard
  // bbox computation loop.
  // Return true if the BBOX was already computed by the class and returned
  // in "bb" so it can be avoided to redo it again. Look at bb.size() to
  // find out the expected dimensionality (e.g. 2 or 3 for point clouds)
  template <class BBOX>
  bool kdtree_get_bbox(BBOX& /* bb */) const {
    return false;
  }

};


template <typename T>
void generateRandomPointCloudRanges(
  PointCloud<T>& pc, const size_t N,
  const T max_range_x, const T max_range_y, const T max_range_z) {

  // generating random point cloud
  pc.pts.resize(N);
  for (size_t i = 0; i < N; i++) {
    pc.pts[i].x = max_range_x * (rand() % 1000) / T(1000);
    pc.pts[i].y = max_range_y * (rand() % 1000) / T(1000);
    pc.pts[i].z = max_range_z * (rand() % 1000) / T(1000);
  }
}


template <typename T>
void generateRandomPointCloud(
  PointCloud<T>& pc, const size_t N, const T max_range = 10) {
  generateRandomPointCloudRanges(pc, N, max_range, max_range, max_range);
}


#endif /* NANOFLANN_UTILS_H */
