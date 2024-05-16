
#include "../include/zones/Zone.hpp"
#include "gtest/gtest.h"

// Define the test fixture for constructor tests
class Zone_Constructor : public ::testing::TestWithParam<std::tuple<std::vector<cv::Point>, int>> {};

// Parameterized test for checking vertices set correctly in the constructor
TEST_P(Zone_Constructor, CheckVertices) {
  auto [verts, expected] = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;

  Zone test_zone(verts, color);
  Point_Set result_vertices = test_zone.get_vertices();
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

// Parameterized test for drawing with insufficient vertices
TEST_P(Insufficient_Verts , DrawWithInsufficientVertices) {
  std::vector<cv::Point> verts = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;
  cv::Mat frame = cv::Mat::zeros(100, 100, CV_8UC3);

  Zone test_zone(verts, color);
  bool results = test_zone.draw(frame);

  EXPECT_FALSE(results);
}

// Instantiate test cases for drawing tests with insufficient vertices
INSTANTIATE_TEST_SUITE_P(InsufficientVertices, Insufficient_Verts , ::testing::Values(
  std::vector<cv::Point>({cv::Point(0,0), cv::Point(10, 10), cv::Point(0, 0)}),
  std::vector<cv::Point>({cv::Point(0,0), cv::Point(10, 10)}),
  std::vector<cv::Point>({cv::Point(0,0)}),
  std::vector<cv::Point>({})
));

class Sufficient_Verts : public ::testing::TestWithParam<std::vector<cv::Point>> {};
// Instantiate test cases for drawing tests with sufficient vertices

// Parameterized test for drawing with sufficient vertices
TEST_P(Sufficient_Verts, DrawWithSufficientVertices) {
  std::vector<cv::Point> verts = GetParam();
  cv::Scalar color(225, 0, 0);
  int thickness = 1;
  cv::Mat frame = cv::Mat::zeros(100, 100, CV_8UC3);

  Zone test_zone(verts, color);
  bool results = test_zone.draw(frame);

  EXPECT_TRUE(results);
}

INSTANTIATE_TEST_SUITE_P(SufficientVertices, Sufficient_Verts, ::testing::Values(
  std::vector<cv::Point>{cv::Point{0, 10}, cv::Point{10, 0}, cv::Point{5, 5}},
  std::vector<cv::Point>{cv::Point{0, 15}, cv::Point{5, 10}, cv::Point{10, 5}, cv::Point{0, 10}},
  std::vector<cv::Point>{cv::Point{0, 0}, cv::Point{10, 0}, cv::Point{5, 5}, cv::Point{10, 10}, cv::Point{0, 10}}
));
