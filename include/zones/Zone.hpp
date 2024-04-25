#ifndef ZONE_HPP
#define ZONE_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <unordered_set>
#include "../utils/Point_Hash.hpp"

class Zone{
  private:
    Point_Set vertices;
    std::vector<std::vector<cv::Point>> poly;
    cv::Scalar color;
    int thickness;

  public:
    Zone(std::vector<cv::Point> verts, cv::Scalar col = cv::Scalar(0, 255, 0), int thick = 2);
    bool draw(cv::Mat &frame) const;
    bool contains(cv::Point &pt) const;
    Point_Set get_vertices() const;
    cv::Scalar get_color() const;
    int get_thickness() const;
};

#endif // ZONE_HPP