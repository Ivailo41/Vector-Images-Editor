#include "ShapeCollection.h"
#include "../Canvas/Canvas.h"

ShapeCollection::ShapeCollection() : shapes(nullptr)
{
    shapes = new Shape*[capacity];
}

ShapeCollection::~ShapeCollection()
{
    free();
}

Shape& ShapeCollection::operator[](unsigned index)
{
    return *shapes[index];
}

const Shape& ShapeCollection::operator[](unsigned index) const
{
    return *shapes[index];
}

void ShapeCollection::addShape(Shape& shape)
{
    if (size == capacity)
    {
        upSize();
    }

    shapes[size++] = &shape;
}

void ShapeCollection::removeShape(unsigned id)
{
    for (int i = 0; i < size; i++)
    {
        if(shapes[i]->getId() == id)
        {
            shapes[i] = nullptr;

            for (unsigned j = i; j < size - 1; ++j)
            {
                shapes[j] = shapes[j + 1];
            }

            --size;

            if (size <= capacity / 2)
            {
                downSize();
            }
        }
    }
}

void ShapeCollection::print() const
{
    for (unsigned i = 0; i < size; ++i)
    {
        shapes[i]->print();
    }
}

void ShapeCollection::translate(double horizontal, double vertical)
{
    for (unsigned i = 0; i < size; ++i)
    {
        shapes[i]->translate(horizontal, vertical);
    }
}

void ShapeCollection::translate(unsigned id, double horizontal, double vertical)
{
    try
    {
        getShapeById(id)->translate(horizontal, vertical);
    }
    catch (const char* error)
    {
        std::cout << error << std::endl;
    }
}

void ShapeCollection::scale(double width, double height)
{
    for (unsigned i = 0; i < size; ++i)
    {
        shapes[i]->scale(width, height);
    }
}

void ShapeCollection::scale(unsigned index, double width, double height)
{
    if (index >= size)
    {
        return;
    }

    shapes[index]->scale(width, height);
}

void ShapeCollection::free()
{
    delete[] shapes;
}

void ShapeCollection::upSize()
{
    capacity *= 2;
    Shape** newShapes = new Shape*[capacity];

    for (unsigned i = 0; i < size; ++i)
    {
        newShapes[i] = shapes[i];
    }

    delete[] shapes;
    shapes = newShapes;
}

void ShapeCollection::downSize()
{
    capacity /= 2;
    Shape** newShapes = new Shape*[capacity];

    for (unsigned i = 0; i < size; ++i)
    {
        newShapes[i] = shapes[i];
    }

    delete[] shapes;
    shapes = newShapes;
}

Shape* ShapeCollection::getShapeById(unsigned id)
{
    for (unsigned i = 0; i < size; ++i)
    {
        if (shapes[i]->getId() == id)
        {
            return shapes[i];
        }
    }

    throw std::invalid_argument("No shape with id " + std::to_string(id) + " found!");
}

void ShapeCollection::clear()
{
    for (unsigned i = 0; i < size; ++i)
    {
        shapes[i] = nullptr;
    }

    size = 0;
}