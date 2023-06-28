#include "Shape.h"
#include <iostream>

unsigned Shape::nextId = 0;

Shape::Shape(unsigned pointsCount) : points(nullptr), pointsCount(pointsCount), id(nextId++),
                                     borderColor(black), fillColor(transparent)
{
    points = new Point[pointsCount];
}

Shape::Shape(const Shape& other) : points(nullptr), id(nextId++)
{
    copyFrom(other);
}

Shape& Shape::operator=(const Shape& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Shape::~Shape()
{
    free();
}

void Shape::copyFrom(const Shape& other)
{
    borderColor = other.borderColor;
    fillColor = other.fillColor;

    pointsCount = other.pointsCount;
    points = new Point[pointsCount];

    for (unsigned i = 0; i < pointsCount; ++i)
    {
        points[i] = other.points[i];
    }
}

void Shape::free()
{
    delete[] points;
}

void Shape::show()
{
    isVisible = true;
}

void Shape::hide()
{
    isVisible = false;
}

void Shape::setInGroup(bool isInGroup)
{
    this->isInGroup = isInGroup;
}

void Shape::setPoint(unsigned index, double x, double y)
{
    if (index >= pointsCount)
    {
        throw std::out_of_range("Invalid index");
    }

    points[index].x = x;
    points[index].y = y;
}

void Shape::setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    borderColor.redValue = r;
    borderColor.greenValue = g;
    borderColor.blueValue = b;
    borderColor.alpha = a;
}

void Shape::setFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    fillColor.redValue = r;
    fillColor.greenValue = g;
    fillColor.blueValue = b;
    fillColor.alpha = a;
}

void Shape::print() const
{
    if(isVisible)
    {
        std::cout << fillColor << " " << borderColor << std::endl;
    }
}