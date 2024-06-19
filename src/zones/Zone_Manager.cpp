#include "../../include/zones/Zone_Manager.hpp"
#include "../../include/zones/Zone.hpp"
#include <opencv2/core.hpp>
#include <iostream>

void Zone_Manager::update_zone_polygons() {
  std::vector<std::vector<cv::Point>> zone_polys;
  for(int i = 0; i < zones.size(); i++) {
    zone_polys.push_back(zones[i]->get_poly());
  }
  this->zone_polygons = zone_polys;
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

bool Zone_Manager::add_zone(std::vector<cv::Point> vertices){
  if(vertices.size() < 3) {
    return false;
  }
  int zone_id = create_zone_id();
  Zone *new_zone = new Zone(vertices, zone_id);
  total_created_zones++;
  zones.push_back(new_zone);
  update_zone_polygons();
  return true;
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
  return nullptr;
}

int Zone_Manager::zone_finder(cv::Point pt) {
  for(int i = 0; i < zones.size(); i++){
    if(zones[i]->contains(pt)){
      return zones[i]->get_id();
    }
  }
  return -1;
}


int Zone_Manager::get_num_zones(){
  return zones.size();
}

void Zone_Manager::draw_zones(cv::Mat &frame) {
  bool zones_valid = validate_zones();
  if(!zones_valid) {
    std::cout << "Zones invalid, cannot draw" << std::endl;
    return;
  }
  cv::fillPoly(frame, zone_polygons, color);
}

bool Zone_Manager::destroy_zone(int zone_id){
  for(int i = 0; zones.size(); i++){
    if(zones[i]->get_id() == zone_id){
      delete zones[i];
      zones.erase(zones.begin() + i);
      update_zone_polygons();
      return true;
    }
  }
  return false;
}

void Zone_Manager::destroy_all_zones() {
  for(int i = 0; i < zones.size(); i++) {
    delete zones[i];
  }
  update_zone_polygons();
  zones.clear();
}