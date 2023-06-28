//
// Created by audit on 14.6.2023 г..
//

#ifndef SVG_PROJECT_SHAPEFACTORY_H
#define SVG_PROJECT_SHAPEFACTORY_H
#include <vector>
#include <string>
#include "../Shapes/Shape.h"
#include "../Shapes/Line.h"
#include "../Shapes/Arc.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Polygon.h"

enum class ShapeType
{
    UNDEFINED = -1,
    ARC,
    LINE,
    POLYGON,
    RECTANGLE,
    COUNT
};

class ShapeFactory
{
public:
    static ShapeFactory& getInstance();

    Shape* createShape(const std::vector<std::string>& arguments) const;
    static std::string getShapeAsSVG(Shape& shape);

private:
    static ShapeFactory shapeFactory;

private:
    ShapeFactory() = default;
    ShapeFactory(const ShapeFactory& other) = delete;
    ShapeFactory& operator=(const ShapeFactory& other) = delete;
    ~ShapeFactory() = default;
};


#endif //SVG_PROJECT_SHAPEFACTORY_H
