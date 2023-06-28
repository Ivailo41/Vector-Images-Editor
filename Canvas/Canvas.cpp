#include "Canvas.h"
#include "../Shapes/Group.h"

Canvas Canvas::canvas;

Canvas& Canvas::getInstance()
{
    return canvas;
}

void Canvas::addShape(Shape& shape)
{
    shapes.addShape(shape);
}

void Canvas::print() const
{
    shapes.print();
}

unsigned Canvas::group(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY)
{
    Group* group = new Group();
    shapes.addShape(*group);

    Point topLeft(topLeftX, topLeftY);
    Point bottomRight(bottomRightX, bottomRightY);

    for(unsigned i = 0; i < shapes.getSize(); i++)
    {
        if(shapes[i].isInsideRegion(topLeft, bottomRight))
        {
            group->addShape(shapes[i]);
        }
    }

    return group->getId();
}

void Canvas::ungroup(unsigned int id)
{
    Group* group = dynamic_cast<Group*>(shapes.getShapeById(id));
    if(group == nullptr)
    {
        std::cout << "Shape with id " << id << " is not a group." << std::endl;
        return;
    }

    shapes.removeShape(id);
    delete group;
}

void Canvas::extractShapeFromGroup(unsigned int groupId, unsigned int shapeId)
{
    Group* group = dynamic_cast<Group*>(shapes.getShapeById(groupId));
    if(group == nullptr)
    {
        std::cout << "Shape with id " << groupId << " is not a group." << std::endl;
        return;
    }

    group->removeShape(shapeId);
}

void Canvas::insertShapeInGroup(unsigned int groupId, unsigned int shapeId)
{
    if(shapes.getShapeById(shapeId)->getIsInGroup())
    {
        std::cout << "Shape with id " << shapeId << " is already in a group." << std::endl;
        return;
    }

    Group* group = dynamic_cast<Group*>(shapes.getShapeById(groupId));
    if(group == nullptr)
    {
        std::cout << "Shape with id " << groupId << " is not a group." << std::endl;
        return;
    }

    group->addShape(*shapes.getShapeById(shapeId));
}

void Canvas::removeShape(unsigned int id)
{
    Shape* shape = shapes.getShapeById(id);
    shapes.removeShape(id);
    delete shape;
}

void Canvas::clearCanvas()
{

    for(unsigned i = 0; i < shapes.getSize(); i++)
    {
        delete &shapes[i];
    }
    shapes.clear();

}

void Canvas::scale(unsigned int id, double x, double y)
{
    if(shapes.getShapeById(id)->getIsInGroup())
    {
        std::cout << "Shape with id " << id << " is in a group and can not edit it individually" << std::endl;
        return;
    }

    shapes.getShapeById(id)->scale(x, y);
}

void Canvas::translate(unsigned int id, double x, double y)
{
    if(shapes.getShapeById(id)->getIsInGroup())
    {
        std::cout << "Shape with id " << id << " is in a group and can not edit it individually" << std::endl;
        return;
    }

    shapes.getShapeById(id)->translate(x, y);
}

void Canvas::scale(double x, double y)
{
    for(unsigned i = 0; i < shapes.getSize(); i++)
    {
        if(!shapes[i].getIsInGroup())
            shapes[i].scale(x, y);
    }
}

void Canvas::translate(double x, double y)
{
    for(unsigned i = 0; i < shapes.getSize(); i++)
    {
        if(!shapes[i].getIsInGroup())
            shapes[i].translate(x, y);
    }
}

void Canvas::showShape(unsigned int id)
{
    if(shapes.getShapeById(id)->getIsInGroup())
    {
        std::cout << "Shape with id " << id << " is in a group and can not edit it individually" << std::endl;
        return;
    }
    shapes.getShapeById(id)->show();
}

void Canvas::hideShape(unsigned int id)
{
    if(shapes.getShapeById(id)->getIsInGroup())
    {
        std::cout << "Shape with id " << id << " is in a group and can not edit it individually" << std::endl;
        return;
    }
    shapes.getShapeById(id)->hide();
}

Shape& Canvas::getShapeAt(unsigned int index)
{
    return shapes[index];
}

void Canvas::setCanvasSize(double x, double y)
{
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    sizeX = x;
    sizeY = y;
}