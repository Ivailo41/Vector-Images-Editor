#ifndef SVG_PROJECT_POLYGON_H
#define SVG_PROJECT_POLYGON_H
#include "Shape.h"

class Polygon : public Shape
{
public:
    void print() const override;
    std::string extract() const override;

    void scale(double width, double height) override;
    void translate(double horizontal, double vertical) override;
    bool isInsideRegion(Point topLeft, Point bottomRight) const override;

public:
    Polygon(unsigned pointsCount);
    Polygon(const Polygon& other) = default;
    Polygon& operator=(const Polygon& other) = default;
    ~Polygon() = default;


protected:
    Point getCenter() const;

};


#endif //SVG_PROJECT_POLYGON_H
