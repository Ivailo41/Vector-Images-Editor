#include "Group.h"

Group::Group() : Shape(1)
{

}

Group::~Group()
{
    for (unsigned i = 0; i < shapes.getSize(); ++i)
    {
        shapes[i].setInGroup(false);
    }
}

void Group::print() const
{
    if(isVisible)
    {
        std::cout << "Group " << id << ": { ";
        for (int i = 0; i < shapes.getSize(); ++i)
        {
            std::cout << shapes[i].getId() << " ";
        }
        std ::cout << "}" << std::endl;
    }
}

void Group::translate(double horizontal, double vertical)
{
    for (unsigned i = 0; i < shapes.getSize(); ++i)
    {
        shapes[i].translate(horizontal, vertical);
    }
}

void Group::scale(double width, double height)
{
    for (unsigned i = 0; i < shapes.getSize(); ++i)
    {
        shapes[i].scale(width, height);
    }
}

void Group::addShape(Shape& shape)
{
    if(shape.getIsInGroup() || this == &shape)
    {
        return;
    }
    shape.setInGroup(true);
    shapes.addShape(shape);
}

void Group::removeShape(unsigned id)
{
    try
    {
        shapes.getShapeById(id)->setInGroup(false);
        shapes.removeShape(id);
    }
    catch(const char* error)
    {
        std::cout << error << std::endl;
    }
}

bool Group::isInsideRegion(Point topLeft, Point bottomRight) const
{
    for (int i = 0; i < shapes.getSize(); ++i)
    {
        if(!shapes[i].isInsideRegion(topLeft, bottomRight))
        {
            return false;
        }
    }
    return true;
}

Shape* Group::getShapeById(unsigned id)
{
    return shapes.getShapeById(id);
}

std::string Group::extract() const
{
    return "";
}

