#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "opencv2/imgproc.hpp"

class Shape {
public:
    Shape(std::vector<cv::Point>& square);
    const bool operator<(const Shape &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
    double centerDist() const;
    void addCircles(std::vector<cv::Vec3f>& circles);
    const std::vector<cv::Point>& getSquare() const;
    const std::vector<cv::Vec3f>& getCircles() const;
private:
    std::vector<cv::Point> m_square;
    std::vector<cv::Vec3f> m_cirlces;
    cv::Point2f m_sqCenter;
    double m_sqAvgEdge;
};

#endif
