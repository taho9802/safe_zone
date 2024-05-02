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
    std::vector<cv::Point> poly;
    int zone_id;

  public:
    Zone(std::vector<cv::Point> verts);
    Zone(std::vector<cv::Point> verts, int id);
    bool contains(cv::Point &pt);
    std::vector<cv::Point> get_poly() const;
    int get_id() const;
};

#endif // ZONE_HPP