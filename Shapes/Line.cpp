#include "Line.h"
#include <iostream>
#include <cmath>

Line::Line() : Shape(2)
{
}

void Line::print() const
{
    if(isVisible)
    {
        std::cout << "Line " << id << ": ";
        for (unsigned i = 0; i < pointsCount; ++i)
        {
            std::cout << points[i] << " ";
        }
        Shape::print();
    }
}

void Line::scale(double width, double height)
{
    Point center((points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2);

    translate(-center.x, -center.y);

    points[0].x *= width;
    points[0].y *= height;

    points[1].x *= width;
    points[1].y *= height;

    translate(center.x, center.y);
}

void Line::translate(double horizontal, double vertical)
{
    for (unsigned i = 0; i < pointsCount; ++i)
    {
        points[i].x += horizontal;
        points[i].y += vertical;
    }
}

bool Line::isInsideRegion(Point topLeft, Point bottomRight) const
{
    Point topLeftLine(std::min(points[0].x,points[1].x), std::min(points[0].y,points[1].y));
    Point bottomRightLine(std::max(points[0].x,points[1].x), std::max(points[0].y,points[1].y));

    return topLeft <= topLeftLine && bottomRightLine <= bottomRight;
}

std::string Line::extract() const
{
    if(!isVisible)
    {
        return "";
    }
    std::string line = "line ";
    line.append(std::to_string(points[0].x) + ' ');
    line.append(std::to_string(points[0].y) + ' ');
    line.append(std::to_string(points[1].x) + ' ');
    line.append(std::to_string(points[1].y) + ' ');
    line.append(fillColor.toString() + ' ');
    line.append(borderColor.toString());

    return line;
}

