
#include "../include/zones/Zone.hpp"
#include "gtest/gtest.h"

// Define the test fixture for constructor tests
class Zone_Constructor : public ::testing::TestWithParam<std::tuple<std::vector<cv::Point>, int>> {};

// Parameterized test for checking vertices set correctly in the constructor
TEST_P(Zone_Constructor, CheckVertices) {
  auto [verts, expected] = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;

  Zone test_zone(verts);
  std::vector<cv::Point> result_vertices = test_zone.get_poly();
  EXPECT_EQ(result_vertices.size(), expected);
}

// Instantiate test cases for the constructor tests
INSTANTIATE_TEST_SUITE_P(DefaultConstructorTests, Zone_Constructor, ::testing::Values(
  std::make_tuple(std::vector<cv::Point>{{10, 0}, {20, 10}, {30, 20}}, 3),
  std::make_tuple(std::vector<cv::Point>{{0, 0}, {20, 20}, {20, 20}}, 2),
  std::make_tuple(std::vector<cv::Point>{{10, 10}, {10, 10}, {10, 10}}, 1),
  std::make_tuple(std::vector<cv::Point>{{10, 20}, {10, 15}, {0, 10}, {10, 0}}, 4)
));

// Define the test fixture for drawing tests
class Insufficient_Verts : public ::testing::TestWithParam<std::vector<cv::Point>> {};

