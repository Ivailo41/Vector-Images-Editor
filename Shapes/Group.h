#ifndef SVG_PROJECT_GROUP_H
#define SVG_PROJECT_GROUP_H
#include "../ShapeCollection/ShapeCollection.h"

class Group : public Shape
{
public:
    void print() const override;
    std::string extract() const override;

    void translate(double horizontal, double vertical) override;
    void scale(double width, double height) override;
    bool isInsideRegion(Point topLeft, Point bottomRight) const override;

    Shape* getShapeById(unsigned id);

    void addShape(Shape& shape);
    void removeShape(unsigned id);

    unsigned getSize() const { return shapes.getSize(); }

public:
    Group();
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;
    ~Group() override;

protected:
    ShapeCollection shapes;

};


#endif //SVG_PROJECT_GROUP_H
