#include "Arc.h"
#include <cmath>

Arc::Arc() : Shape(1), radius(1), startAngle(0), arcWidth(360)
{
}

Arc::Arc(const Arc& other) : Shape(other), radius(other.radius), startAngle(other.startAngle), arcWidth(other.arcWidth)
{

}

Arc& Arc::operator=(const Arc& other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        radius = other.radius;
        startAngle = other.startAngle;
        arcWidth = other.arcWidth;
    }

    return *this;
}

void Arc::setRadius(unsigned radius)
{
    this->radius = radius;
}

void Arc::setStartAngle(short startAngle)
{
    if(startAngle < -360)
    {
        startAngle = -360;
    }
    else if(startAngle > 360)
    {
        startAngle = 360;
    }
    this->startAngle = startAngle;
}

void Arc::setArcWidth(short arcWidth)
{
    if(arcWidth < -360)
    {
        arcWidth = -360;
    }
    else if(arcWidth > 360)
    {
        arcWidth = 360;
    }
    this->arcWidth = arcWidth;
}

void Arc::scale(double width, double height)
{
    radius *= width;
}

void Arc::translate(double horizontal, double vertical)
{
    points[0].x += horizontal;
    points[0].y += vertical;
}

void Arc::print() const
{
    if(isVisible)
    {
        std::cout << "Arc " << id << ": ";
        std::cout << points[0] << " ";
        std::cout << "Radius: " << radius << " Start angle: " << startAngle << " Arc width: " << arcWidth << " ";
        Shape::print();
    }
}

bool Arc::isInsideRegion(Point topLeft, Point bottomRight) const
{
    Point topLeftArc(points[0].x - radius, points[0].y - radius);
    Point bottomRightArc(points[0].x + radius, points[0].y + radius);

    return topLeft <= topLeftArc && bottomRightArc <= bottomRight;
}

std::string Arc::extract() const
{
    if(!isVisible)
    {
        return "";
    }
    std::string line = "arc ";
    line.append(std::to_string(points[0].x) + ' ');
    line.append(std::to_string(points[0].y) + ' ');
    line.append(std::to_string(radius) + ' ');
    line.append(std::to_string(startAngle) + ' ');
    line.append(std::to_string(arcWidth) + ' ');
    line.append(fillColor.toString() + ' ');
    line.append(borderColor.toString());

    return line;
}

Point Arc::getPointByAngle(double centerX, double centerY, unsigned radius, short angle)
{
    Point point;

    point.x = centerX + radius * cos(angle * 3.14/180);
    point.y = centerY + radius * sin(angle * 3.14/180);

    return point;
}