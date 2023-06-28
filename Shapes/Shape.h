#ifndef SVG_PROJECT_SHAPE_H
#define SVG_PROJECT_SHAPE_H
#include "Point.h"
#include "Color.h"
#include <vector>
#include <string>

class Shape
{
public:
    virtual void print() const = 0;
    virtual std::string extract() const = 0;
    virtual void scale(double width, double height) = 0;
    virtual void translate(double horizontal, double vertical) = 0;

    virtual bool isInsideRegion(Point topLeft, Point bottomRight) const = 0;

    void setPoint(unsigned index, double x, double y);
    void show();
    void hide();

    void setInGroup(bool isInGroup);
    bool getIsInGroup() const { return isInGroup; }

    unsigned getId() const { return id; }

    void setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void setFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    Color getBorderColor() const { return borderColor; }
    Color getFillColor() const { return fillColor; }

    static unsigned getNextId() { return nextId; }

public:
    Shape(unsigned pointsCount);
    Shape(const Shape& other);
    Shape& operator=(const Shape& other);
    virtual ~Shape();

protected:
    void copyFrom(const Shape& other);
    void free();

protected:
    Point* points;
    unsigned pointsCount;
    unsigned id;
    bool isVisible = true;
    bool isInGroup = false;
    Color borderColor;
    Color fillColor;

    static unsigned nextId;
};


#endif //SVG_PROJECT_SHAPE_H
