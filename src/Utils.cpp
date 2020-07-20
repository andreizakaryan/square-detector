#include "Utils.h"

double calculateAngle(const cv::Point& p1, const cv::Point& p2, const cv::Point& p3) 
{
    cv::Point a = p2 - p1;
    cv::Point b = p2 - p3;
    double dot = (a.x*b.x + a.y*b.y);
    double mod_a = cv::sqrt(a.x*a.x + a.y*a.y);
    double mod_b = cv::sqrt(b.x*b.x + b.y*b.y);
    return std::acos(dot / (mod_a*mod_b)) * 90 / acos(0);
}