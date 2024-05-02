#include "../../include/zones/Zone_Manager.hpp"
#include "../../include/zones/Zone.hpp"
#include <opencv2/core.hpp>
#include <iostream>

Zone_Manager::Zone_Manager() {
  zones = {};
  color = cv::Scalar(255,0,0); //default color red
  total_created_zones = 0;
}

Zone_Manager::Zone_Manager(cv::Scalar color) {
  zones = {};
  this->color = color;
  total_created_zones = 0;
}

int Zone_Manager::zone_finder(cv::Point pt) {
  for(int i = 0; i < zones.size(); i++){
    if(zones[i]->contains(pt)){
      return zones[i]->get_id();
    }
  }
  return -1;
}

bool Zone_Manager::validate_zones(){
  for(int i = 0; i < zones.size(); i++){
    if(zones[i]->get_poly().size() < 3){
      return false;
    }
  }
  return true;
}

int Zone_Manager::create_zone_id(){
  return total_created_zones;
}

void Zone_Manager::add_zone(std::vector<cv::Point> vertices){
  int zone_id = create_zone_id();
  Zone *new_zone = new Zone(vertices, zone_id);
  total_created_zones++;
  zones.push_back(new_zone);
  zone_polygons.push_back(new_zone->get_poly());
}

Zone* Zone_Manager::get_zone(cv::Point pt) {
  int zone_id = zone_finder(pt);
  if(zone_id == -1) {
    return nullptr;
  }
  for(int i = 0; i < zones.size(); i++){
    if(zones[i]->get_id() == zone_id){
      return zones[i];
    }
  }
}

void Zone_Manager::draw_zones(cv::Mat &frame) {
  bool zones_valid = validate_zones();
  if(!zones_valid) {
    std::cout << "Zones invalid, cannot draw" << std::endl;
    return;
  }
  cv::fillPoly(frame, zone_polygons, color);
}

void Zone_Manager::destroy_all_zones() {
  for(int i = 0; i < zones.size(); i++) {
    delete zones[i];
  }
  zones.clear();
}