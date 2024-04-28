#ifndef ZONE_HPP
#define ZONE_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <unordered_set>
#include "../utils/Point_Hash.hpp"

class Zone{
  private:
    Point_Set vertices; //unordered set that contains zone verticies as cv::Points
    std::vector<std::vector<cv::Point>> poly;
    cv::Scalar color;
    int zone_id;

  public:
    Zone(std::vector<cv::Point> verts, cv::Scalar col);
    bool draw(cv::Mat &frame) const;
    bool contains(cv::Point &pt);
    Point_Set get_vertices() const;
    cv::Scalar get_color() const;
};

#endif // ZONE_HPP