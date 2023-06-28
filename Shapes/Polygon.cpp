#include "Polygon.h"

Polygon::Polygon(unsigned pointsCount) : Shape(pointsCount)
{

}

void Polygon::scale(double width, double height)
{
    Point center = getCenter();
    translate(-center.x, -center.y);

    for (unsigned i = 0; i < pointsCount; ++i)
    {
        points[i].x *= width;
        points[i].y *= height;
    }

    translate(center.x, center.y);
}

void Polygon::translate(double horizontal, double vertical)
{
    for (unsigned i = 0; i < pointsCount; ++i)
    {
        points[i].x += horizontal;
        points[i].y += vertical;
    }
}

void Polygon::print() const
{
    if(isVisible)
    {
        std::cout << "Polygon " << id << ": ";
        for (unsigned i = 0; i < pointsCount; ++i)
        {
            std::cout << points[i] << " ";
        }
        Shape::print();
    }
}

bool Polygon::isInsideRegion(Point topLeft, Point bottomRight) const
{
    Point topLeftPoly;
    Point bottomRightPoly;

    for (int i = 0; i < pointsCount; ++i)
    {
        if(points[i].x > bottomRightPoly.x)
        {
            bottomRightPoly.x = points[i].x;
        }
        if(points[i].y > bottomRightPoly.y)
        {
            bottomRightPoly.y = points[i].y;
        }
        if(points[i].x < topLeftPoly.x)
        {
            topLeftPoly.x = points[i].x;
        }
        if(points[i].y < topLeftPoly.y)
        {
            topLeftPoly.y = points[i].y;
        }
    }

    return topLeft <= topLeftPoly && bottomRightPoly <= bottomRight;
}

Point Polygon::getCenter() const
{
    Point center;
    for (unsigned i = 0; i < pointsCount; ++i)
    {
        center.x += points[i].x;
        center.y += points[i].y;
    }
    center.x /= pointsCount;
    center.y /= pointsCount;
    return center;
}

std::string Polygon::extract() const
{
    if(!isVisible)
    {
        return "";
    }
    std::string line = "polygon ";
    for (unsigned i = 0; i < pointsCount; ++i)
    {
        line.append(std::to_string(points[i].x) + ' ');
        line.append(std::to_string(points[i].y) + ' ');
    }
    line.append(fillColor.toString() + ' ');
    line.append(borderColor.toString());

    return line;
}