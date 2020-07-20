#ifndef SQUARE_DETECTOR_H
#define SQUARE_DETECTOR_H

#include <vector>
#include "opencv2/imgproc.hpp"

class SquareDetector {
public:
    SquareDetector(double maxRatio, double angleEpsilon);
    void detectSquares(std::vector<std::vector<cv::Point>>& squares, cv::Mat& img);
private:
    void filterIntersecting(std::vector<std::vector<cv::Point>>& filtered, std::vector<std::vector<cv::Point>>& squares, cv::Mat& img);
    bool isSquare(std::vector<cv::Point>& poly);
    
    double m_maxRatio;
    double m_angleEpsilon;
};

#endif
