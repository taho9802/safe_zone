#include "../include/zones/Zone.hpp"
#include "gtest/gtest.h"

TEST(ZoneTest, Constructor) {
  std::vector<cv::Point> verts = {{0, 0}, {10, 10}, {0, 10}};
  cv::Scalar color(255, 0, 0);  // Red
  int thickness = 1;

  Zone test_zone(verts, color, thickness);
  EXPECT_EQ(thickness, test_zone.get_thickness());
}

TEST(ZoneTest, Draw) {
  std::vector<cv::Point> verts = {{0, 0}, {10, 10}, {0, 10}};
  cv::Scalar color(225, 0, 0);
  int thickness = 1;

  cv::Mat frame = cv::Mat::zeros(100,100,CV_8UC3);
  Zone test_zone(verts, color, thickness);
  bool results = test_zone.draw(frame);

  EXPECT_TRUE(results);
}
