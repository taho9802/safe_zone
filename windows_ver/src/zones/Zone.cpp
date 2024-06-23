#include "../include/zones/Zone.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
Zone::Zone(std::vector<cv::Point> vertices){
  for(int i = 0; i < vertices.size(); i++){
    this->vertices.insert(vertices[i]);
  }
  poly = {std::vector<cv::Point>(this->vertices.begin(), this->vertices.end())};
  zone_id = -1;
}

Zone::Zone(std::vector<cv::Point> vertices, int zone_id){
  for(int i = 0; i < vertices.size(); i++) {
    this->vertices.insert(vertices[i]);
  }
  poly = {std::vector<cv::Point>(this->vertices.begin(), this->vertices.end())};
  this->zone_id = zone_id;
}

bool Zone::contains(cv::Point &pt){
  return cv::pointPolygonTest(poly, pt, false) >= 0;
}

std::vector<cv::Point> Zone::get_poly() const {
  return poly;
}

int Zone::get_id() const {
  return zone_id;
}