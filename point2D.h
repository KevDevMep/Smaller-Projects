#pragma once
#include<iostream>
using namespace std;

class Point
{
public:
    int m_x{};
    int m_y{};
public:
    Point(int x, int y)
    : m_x{x}, m_y{y} 
    { 
    }

    Point()
    : m_x{0}, m_y{0} 
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    friend std::istream& operator>> (std::istream& in, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ')';
    return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
    in >> point.m_x;
    in >> point.m_y;

    return in;
}