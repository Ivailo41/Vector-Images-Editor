#include "Rectangle.h"

Rectangle::Rectangle() : Shape(1), width(1), height(1)
{

}

Rectangle::Rectangle(const Rectangle& other) : Shape(other), width(other.width), height(other.height)
{

}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        width = other.width;
        height = other.height;
    }

    return *this;
}

void Rectangle::setWidth(unsigned width)
{
    this->width = width;
}

void Rectangle::setHeight(unsigned height)
{
    this->height = height;
}

void Rectangle::scale(double width, double height)
{
    this->width *= width;
    this->height *= height;
}

void Rectangle::translate(double horizontal, double vertical)
{
    points[0].x += horizontal;
    points[0].y += vertical;
}

void Rectangle::print() const
{
    if(isVisible)
    {
        std::cout << "Rectangle " << id << ": ";
        std::cout << points[0] << " ";
        std::cout << "Width: " << width << " Height: " << height << " ";
        Shape::print();
    }
}

bool Rectangle::isInsideRegion(Point topLeft, Point bottomRight) const
{
    return topLeft <= points[0] && Point(points[0].x + width, points[0].y + height) <= bottomRight;
}

std::string Rectangle::extract() const
{
    if(!isVisible)
    {
        return "";
    }
    std::string line = "rectangle ";
    line.append(std::to_string(points[0].x) + ' ');
    line.append(std::to_string(points[0].y) + ' ');
    line.append(std::to_string(width) + ' ');
    line.append(std::to_string(height) + ' ');
    line.append(fillColor.toString() + ' ');
    line.append(borderColor.toString());

    return line;
}