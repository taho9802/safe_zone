#include "../include/zones/Zone_Manager.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

void populate_zone(std::vector<std::vector<cv::Point>> verts, Zone_Manager &zm){
  for(int i = 0; i < verts.size(); i++){
    zm.add_zone(verts[i]);
  }
}

// Define the test fixture for constructor tests
class Zone_Manager_Test : public testing::Test {
  protected:
    Zone_Manager test = Zone_Manager();
};

TEST_F(Zone_Manager_Test, add_valid_zone){
  std::vector<cv::Point> vertices = {cv::Point(0, 0), cv::Point(0, 50), cv::Point(50, 50)};
  bool status = test.add_zone(vertices);
  EXPECT_TRUE(status);
  EXPECT_EQ(test.get_num_zones(), 1);
}

TEST_F(Zone_Manager_Test, add_invalid_zone){
  std::vector<cv::Point> vertices = {cv::Point(0, 0), cv::Point(0, 50)};
  bool status = test.add_zone(vertices);
  EXPECT_FALSE(status);
  EXPECT_EQ(test.get_num_zones(), 0);
}

TEST_F(Zone_Manager_Test, remove_zone){
  std::vector<std::vector<cv::Point>> verts = {
    {cv::Point(0, 0), cv::Point(0, 50), cv::Point(50, 50)},
    {cv::Point(0, 80), cv::Point(80, 80), cv::Point(160, 160)},
    {cv::Point(80, 0), cv::Point(160, 0), cv::Point(160, 80)}
  };

  populate_zone(verts, test);
  bool status = test.destroy_zone(0);


  EXPECT_TRUE(status);
  EXPECT_EQ(test.get_num_zones(), 2);
}