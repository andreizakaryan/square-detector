#include "SquareDetector.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include "opencv2/highgui.hpp"


SquareDetector::SquareDetector(double maxRatio, double angleEpsilon) :
    m_maxRatio(maxRatio), m_angleEpsilon(angleEpsilon)
{
}

void SquareDetector::detectSquares(std::vector<std::vector<cv::Point>>& squares, cv::Mat& img)
{
    squares.clear();
    std::vector<std::vector<cv::Point>> allSquares;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); i++)
    {
        double arclen = cv::arcLength(contours[i], true);
        std::vector<cv::Point> poly;
        cv::approxPolyDP(contours[i], poly, 0.04 * arclen, true);
        if (cv::contourArea(poly) > 500 && cv::isContourConvex(poly) && isSquare(poly))
        {
            allSquares.push_back(poly);
        }
    }
    filterIntersecting(squares, allSquares, img);
}

bool SquareDetector::isSquare(std::vector<cv::Point>& poly)
{
    if (poly.size() != 4)
    {
        return false;
    }
    std::vector<double> dists;
    for (size_t i = 0; i < 4; i++)
    {
        double dist = calculateDist<cv::Point>(poly[i], poly[(i+1) % 4]);
        dists.push_back(dist);
        double angle = calculateAngle(poly[(i-1) % 4], poly[i], poly[(i+1) % 4]);
        if (cv::abs(90 - angle) > m_angleEpsilon) {
            return false;
        }
    }
    std::sort(dists.begin(), dists.end());
    if (dists.back() / dists.front() > m_maxRatio) 
    {
        return false;
    }
    return true;
}

void SquareDetector::filterIntersecting(std::vector<std::vector<cv::Point>>& filtered, std::vector<std::vector<cv::Point>>& squares, cv::Mat& img)
{
    filtered.clear();
    std::sort(squares.begin(), squares.end(), 
        [](const std::vector<cv::Point> & a, const std::vector<cv::Point> & b) {
            return cv::contourArea(a) > cv::contourArea(b);
        } 
    );
    cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    for (size_t i = 0; i < squares.size(); i++) 
    {
        cv::Mat sqMask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
        cv::drawContours(sqMask, squares, (int)i, 255, cv::FILLED);
        cv::Mat intersection = (mask & sqMask);
        int nonZeros = cv::countNonZero(intersection);
        if (nonZeros == 0) {
            cv::drawContours(mask, squares, (int)i, 255, cv::FILLED);
            filtered.push_back(squares[i]);
        }
    }
    
} 