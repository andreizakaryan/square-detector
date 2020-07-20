#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include "Shape.h"
#include <vector>
#include "opencv2/imgproc.hpp"

class ShapeDetector {
public:
    ShapeDetector();
    void detectShapes(std::vector<Shape>& shapes, std::vector<std::vector<cv::Point>>& squares, cv::Mat& img);
private:
    void detectCircles(std::vector<cv::Vec3f>& circles, std::vector<cv::Point>& square, cv::Mat& img);
};

#endif
