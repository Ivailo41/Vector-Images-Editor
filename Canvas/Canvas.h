#ifndef SVG_PROJECT_CANVAS_H
#define SVG_PROJECT_CANVAS_H
#include "../ShapeCollection/ShapeCollection.h"
#include <vector>

//singleton
class Canvas
{
public:
    static Canvas& getInstance();

    void addShape(Shape& shape);
    void removeShape(unsigned id);
    void print() const;

    unsigned group(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY); //returns group id
    void ungroup(unsigned id);

    void scale(unsigned id, double x, double y);
    void translate(unsigned id, double x, double y);
    void scale(double x, double y);
    void translate(double x, double y);
    void showShape(unsigned id);
    void hideShape(unsigned id);

    bool isCanvasEmpty() const { return shapes.getSize() == 0; }
    void clearCanvas();

    void extractShapeFromGroup(unsigned groupId, unsigned shapeId);
    void insertShapeInGroup(unsigned groupId, unsigned shapeId);

    Shape& getShapeAt(unsigned index);
    unsigned getShapesCount() const { return shapes.getSize(); }

    Point getCanvasSize() const { return Point(sizeX, sizeY); }
    void setCanvasSize(double x, double y);

public:
    std::string currentFileName;

private:
    Canvas() = default;
    Canvas(const Canvas& other) = delete;
    Canvas& operator=(const Canvas& other) = delete;
    ~Canvas() = default;

private:
    ShapeCollection shapes;
    static Canvas canvas;
    double sizeX = 1000;
    double sizeY = 1000;
};


#endif //SVG_PROJECT_CANVAS_H
