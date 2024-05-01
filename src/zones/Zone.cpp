#include "../include/zones/Zone.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
Zone::Zone(std::vector<cv::Point> verts, cv::Scalar col){
  for(int i = 0; i < verts.size(); i++){
    vertices.insert(verts[i]);
  }
  poly = {std::vector<cv::Point>(vertices.begin(), vertices.end())};
  zone_id = -1;
}

bool Zone::draw(cv::Mat &frame) const {
  std::cout <<  "Drawing zone with " << vertices.size() << " vertices" << std::endl;
  if(vertices.size() < 3) {
    std::cout << "Zone must have at least 3 unique vertices" << std::endl;
    return false;
  }
  cv::fillPoly(frame, poly, color);
  return true;
}

bool Zone::contains(cv::Point &pt){
  return cv::pointPolygonTest(poly, pt, false) >= 0;
}

Point_Set Zone::get_vertices() const {
  return vertices;
}

cv::Scalar Zone::get_color() const {
  return color;
}

int Zone::get_id() const {
  return zone_id;
}