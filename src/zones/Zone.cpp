#include "../include/zones/Zone.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
Zone::Zone(std::vector<cv::Point> verts, cv::Scalar col, int thick)
    : color(col), thickness(thick) {
      for (const auto& vertex: verts) {
        vertices.insert(vertex);
      }
      poly.push_back(verts);
    }

bool Zone::draw(cv::Mat &frame) const {
  if(vertices.size() < 3) {
    std::cout << "Zone must have at least 3 vertices" << std::endl;
    return false;
  }
  cv::fillPoly(frame, poly, color, cv::LINE_8, 0, cv::Point());
  return true;
}

bool Zone::contains(cv::Point &pt) const {
  return cv::pointPolygonTest(poly, pt, false) >= 0;
}

Point_Set Zone::get_vertices() const {
  return vertices;
}

cv::Scalar Zone::get_color() const {
  return color;
}

int Zone::get_thickness() const {
  return thickness;
}