#include "Shape.h"
#include "Utils.h"

Shape::Shape(std::vector<cv::Point>& square) : m_square(square)
{
    cv::Moments m = cv::moments(square);
    m_sqCenter.x = m.m10/m.m00;
    m_sqCenter.y = m.m01/m.m00;
    m_sqAvgEdge = 0;
    for (size_t i = 0; i < 4; i++)
    {
        m_sqAvgEdge += calculateDist(square[i], square[(i+1) % 4]);
    }
    m_sqAvgEdge /= 4;
}

const bool Shape::operator<(const Shape &other) const
{
    if (m_cirlces.size() == 0 || other.m_cirlces.size() == 0) {
        return false;
    }
    return centerDist() < other.centerDist();
}

double Shape::centerDist() const{
    return calculateDist<cv::Point2f>(m_sqCenter, cv::Point2f(m_cirlces[0][0], m_cirlces[0][1])) / m_sqAvgEdge;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape) 
{
    const std::vector<cv::Point>& square = shape.getSquare();
    for (size_t i = 0; i < square.size(); i++) 
    {
        os << square[i] << " ";
    }
    return os;
}

void Shape::addCircles(std::vector<cv::Vec3f>& circles)
{
    m_cirlces = circles;
}

const std::vector<cv::Point>& Shape::getSquare() const
{
    return m_square;
}

const std::vector<cv::Vec3f>& Shape::getCircles() const
{
    return m_cirlces;
}