#ifndef POINT_HASH_HPP
#define POINT_HASH_HPP
#include <opencv2/core.hpp>
#include <unordered_set>
#include <functional>
#include <opencv2/core/types.hpp>

struct Point_Hash {
  std::size_t operator()(const cv::Point& p) const {
    return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
  }
};

struct Point_Equal {
  bool operator()(const cv::Point& p1, const cv::Point& p2) const {
    return p1.x == p2.x && p1.y == p2.y;
  }
};

using Point_Set = std::unordered_set<cv::Point, Point_Hash, Point_Equal>;
#endif // POINT_HASH_HPP