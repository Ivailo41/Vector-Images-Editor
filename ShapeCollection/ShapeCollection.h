#ifndef SVG_PROJECT_SHAPECOLLECTION_H
#define SVG_PROJECT_SHAPECOLLECTION_H
#include "../Shapes/Shape.h"

class ShapeCollection
{
public:
    void addShape(Shape& shape);
    void removeShape(unsigned index);

    void print() const;

    void translate(double horizontal, double vertical);
    void translate(unsigned index, double horizontal, double vertical);

    void scale(double width, double height);
    void scale(unsigned index, double width, double height);

    unsigned getSize() const { return size; }
    Shape* getShapeById(unsigned id);

    void clear();

public:
    ShapeCollection();
    ShapeCollection(const ShapeCollection& other) = delete;
    ShapeCollection& operator=(const ShapeCollection& other) = delete;
    ~ShapeCollection();

    Shape& operator[](unsigned index);
    const Shape& operator[](unsigned index) const;

private:
    Shape** shapes;
    unsigned size = 0;
    unsigned capacity = 4;

private:
    void upSize();
    void downSize();
    void free();

};


#endif //SVG_PROJECT_SHAPECOLLECTION_H
