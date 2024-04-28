#ifndef ZONE_MANAGER_HPP
#define ZONE_MANAGER_HPP

#include <vector>
#include "Zone.hpp"

class Zone_Manager {
  private:
    std::vector<Zone> zones;
  public:
    Zone_Manager();
    void add_zone(Zone zone);
    Zone get_zone();
    void delete_zone();
    void handle_mouse_click(int event, int x, int y, int flags);
    void handle_key_click(int key);
    void draw_zones(cv::Mat &frame);
    int create_zone_id();
};

#endif // ZONE_MANAGER_HPP