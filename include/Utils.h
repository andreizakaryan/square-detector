#ifndef UTILS_H
#define UTILS_H

#include "opencv2/imgproc.hpp"
#include <cmath>

template <typename T>
double calculateDist(const T& p, const T& q) 
{
    T diff = p - q;
    return cv::sqrt(diff.x*diff.x + diff.y*diff.y);
}

double calculateAngle(const cv::Point& p1, const cv::Point& p2, const cv::Point& p3);

#endif