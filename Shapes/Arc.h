#ifndef SVG_PROJECT_ARC_H
#define SVG_PROJECT_ARC_H
#include "Shape.h"

class Arc : public Shape
{

public:
    void print() const override;
    std::string extract() const override;

    void scale(double width, double height) override;
    void translate(double horizontal, double vertical) override;
    bool isInsideRegion(Point topLeft, Point bottomRight) const override;

    void setRadius(unsigned radius);
    void setStartAngle(short startAngle);
    void setArcWidth(short arcWidth);

    unsigned getRadius() const { return radius; }
    short getStartAngle() const { return startAngle; }
    short getArcWidth() const { return arcWidth; }

    static Point getPointByAngle(double centerX, double centerY, unsigned radius, short angle); //returns the point on the arc with the given angle

public:
    Arc();
    Arc(const Arc& other);
    Arc& operator=(const Arc& other);
    ~Arc() override = default;

protected:
    unsigned radius;
    short startAngle; //in degrees
    short arcWidth; //in degrees

};


#endif //SVG_PROJECT_ARC_H
