#ifndef ZONE_MANAGER_HPP
#define ZONE_MANAGER_HPP

#include <vector>
#include <opencv2/core.hpp>
#include "Zone.hpp"

class Zone_Manager {
  private:
    std::vector<Zone*> zones;
    std::vector<std::vector<cv::Point>> zone_polygons;
    int total_created_zones;
    cv::Scalar color;

    int zone_finder(cv::Point pt);
    bool validate_zones();
    int create_zone_id();
  public:
    Zone_Manager();
    Zone_Manager(cv::Scalar color);
    bool add_zone(std::vector<cv::Point> vertices);
    Zone* get_zone(cv::Point pt);
    void delete_zone();
    void draw_zones(cv::Mat &frame);
    bool destroy_zone(int zone_id);
    void destroy_all_zones();
};

#endif // ZONE_MANAGER_HPP