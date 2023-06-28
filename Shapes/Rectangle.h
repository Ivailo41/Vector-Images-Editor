#ifndef SVG_PROJECT_RECTANGLE_H
#define SVG_PROJECT_RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape
{
public:
    void print() const override;
    std::string extract() const override;

    void scale(double width, double height) override;
    void translate(double horizontal, double vertical) override;
    bool isInsideRegion(Point topLeft, Point bottomRight) const override;

    void setWidth(unsigned width);
    void setHeight(unsigned height);

    unsigned getWidth() const { return width; }
    unsigned getHeight() const { return height; }

public:
    Rectangle();
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    ~Rectangle() override = default;

protected:
    unsigned width;
    unsigned height;

};


#endif //SVG_PROJECT_RECTANGLE_H
