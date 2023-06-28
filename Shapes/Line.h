//
// Created by audit on 5.6.2023 г..
//

#ifndef SVG_PROJECT_LINE_H
#define SVG_PROJECT_LINE_H
#include "Shape.h"


class Line : public Shape
{

public:
    void print() const override;
    std::string extract() const override;

    void scale(double width, double height) override;
    void translate(double horizontal, double vertical) override;
    bool isInsideRegion(Point topLeft, Point bottomRight) const override;

public:
    Line();
    Line(const Line& other) = default;
    Line& operator=(const Line& other) = default;
    ~Line() = default;

protected:

};


#endif //SVG_PROJECT_LINE_H
