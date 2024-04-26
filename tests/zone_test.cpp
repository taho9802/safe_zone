#include "../include/zones/Zone.hpp"
#include "gtest/gtest.h"

class Zone_Constructor : public ::testing::TestWithParam<std::tuple<std::vector<cv::Point>, int>> {};

TEST_P(Zone_Constructor, check_vertices) {
  cv::Scalar color(225, 0, 0);
  int thickness = 1;

  auto [verts, expected] = GetParam();
  Zone test_zone(verts, color, thickness);

  Point_Set result_vertices = test_zone.get_vertices();
  EXPECT_EQ(result_vertices.size(), expected);
}

INSTANTIATE_TEST_SUITE_P(check_vertices, Zone_Constructor, ::testing::Values(
  std::make_tuple(std::vector<cv::Point>{{10, 0}, {20, 10}, {30, 20}}, 3),
  std::make_tuple(std::vector<cv::Point>{{0, 0}, {20, 20}, {20, 20}}, 2),
  std::make_tuple(std::vector<cv::Point>{{10, 10}, {10, 10}, {10, 10}}, 1),
  std::make_tuple(std::vector<cv::Point>{{10, 20}, {10, 15}, {0, 10}, {10, 0}}, 4)
));

class Zone_Test : public testing::TestWithParam<std::vector<cv::Point>> {};

TEST_P(Zone_Test, draw_with_insufficient_vertices) {
  std::vector<cv::Point> verts = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;
  cv::Mat frame = cv::Mat::zeros(100, 100, CV_8UC3);

  Zone test_zone(verts, color, thickness);
  bool results = test_zone.draw(frame);

  EXPECT_FALSE(results);
}

INSTANTIATE_TEST_SUITE_P(draw_with_insufficient_vertices, Zone_Test, ::testing::Values(
  std::vector<cv::Point>({cv::Point(0,0), cv::Point(10, 10), cv::Point(0, 0)}),
  std::vector<cv::Point>({cv::Point(0,0), cv::Point(10, 10)}),
  std::vector<cv::Point>({cv::Point(0,0)}),
  std::vector<cv::Point>({})
));

TEST_P(Zone_Test, draw_with_sufficient_vertices) {
  std::vector<cv::Point> verts = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;
  cv::Mat frame = cv::Mat::zeros(100, 100, CV_8UC3);
  Zone test_zone(verts, color, thickness);

  bool results = test_zone.draw(frame);

  EXPECT_TRUE(results);
}

INSTANTIATE_TEST_SUITE_P(draw_with_sufficient_vertices, Zone_Test, ::testing::Values(
  std::vector<cv::Point>({cv::Point(0, 10), cv::Point(10, 0), cv::Point(5, 5)}),
  std::vector<cv::Point>({cv::Point(0, 15), cv::Point(5, 10), cv::Point(10, 5), cv::Point(0, 10)}),
  std::vector<cv::Point>({cv::Point(0, 0), cv::Point(10, 0), cv::Point(5, 5), cv::Point(10, 10), cv::Point(0, 10)})
));