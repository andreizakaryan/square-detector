#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

#include "SquareDetector.h"
#include "ShapeDetector.h"

const int lowThreshold = 85;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";
cv::RNG rng(12345);


void drawShapes(std::vector<Shape>& shapes, cv::Mat& img)
{
    for (size_t i = 0; i < shapes.size(); i++) {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
        const std::vector<cv::Point>& square = shapes[i].getSquare();
        cv::drawContours(img, std::vector<std::vector<cv::Point>> {square}, 0, color, 2, cv::LINE_8);
        const std::vector<cv::Vec3f>& circles = shapes[i].getCircles();
        for( size_t j = 0; j < circles.size(); j++)
        {
            cv::Point center(cvRound(circles[j][0]), cvRound(circles[j][1]));
            int radius = cvRound(circles[j][2]);
            cv::circle(img, center, radius, color, 2, cv::LINE_8, 0);
        }
    }
    cv::namedWindow(window_name);
    cv::imshow(window_name, img);
    cv::waitKey(0);
}

//void sortShapes() 

int main( int argc, char** argv )
{
    cv::Mat src, src_gray, edges;
    if (argc < 2) {
        std::cerr << "Add the image path as a command line argument\n" << std::endl;
        return -1;
    }
    src = cv::imread(argv[1], cv::IMREAD_COLOR); 
    if( src.empty())
    {
        std::cerr << "Could not open the image\n" << std::endl;
        return -1;
    }
    
    //preprocessing
    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    cv::blur(src_gray, edges, cv::Size(3, 3));
    cv::Canny(edges, edges, lowThreshold, lowThreshold*ratio, kernel_size);
    
    //square detection
    std::vector<std::vector<cv::Point>> squares;
    SquareDetector sqDetector(1.15, 10);
    sqDetector.detectSquares(squares, edges);
    
    //shape detection (circles inside squares)
    std::vector<Shape> shapes;
    ShapeDetector shDetector;
    shDetector.detectShapes(shapes, squares, src_gray);


    //print squares
    std::sort(shapes.begin(), shapes.end());
    for (size_t i = 0; i < shapes.size(); i++) {
        std::cout << shapes[i] << std::endl;
    }

    drawShapes(shapes, src);
    return 0;
}