#include "ShapeDetector.h"

ShapeDetector::ShapeDetector() 
{}

void ShapeDetector::detectShapes(std::vector<Shape>& shapes, std::vector<std::vector<cv::Point>>& squares, cv::Mat& img)
{
    shapes.clear();
    for (size_t i = 0; i < squares.size(); i++) 
    {
        std::vector<cv::Vec3f> circles;
        detectCircles(circles, squares[i], img);
        if (circles.size() > 0) 
        {
            Shape shape(squares[i]);
            shape.addCircles(circles);
            shapes.push_back(shape);
        }
    }
}

void ShapeDetector::detectCircles(std::vector<cv::Vec3f>& circles, std::vector<cv::Point>& square, cv::Mat& img) 
{
    cv::Rect rect = cv::boundingRect(square);
    cv::Mat cropped = img(rect);
    cv::HoughCircles(cropped, circles, cv::HOUGH_GRADIENT, 1, cropped.rows/4, 200, 50, cropped.rows/4, cropped.rows/2);
    for (size_t i = 0; i < circles.size(); i++)
    {
        circles[i][0] += rect.x;
        circles[i][1] += rect.y;
    }
}
