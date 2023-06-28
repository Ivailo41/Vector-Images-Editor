#include "ShapeFactory.h"
#include "../CommandListener/CommandListener.h"

ShapeFactory ShapeFactory::shapeFactory;

ShapeFactory& ShapeFactory::getInstance()
{
    return shapeFactory;
}

Shape* ShapeFactory::createShape(const std::vector<std::string>& arguments) const
{
    try
    {
        if (arguments[0] == "arc")
        {
            if(arguments.size() != 8)
            {
                throw std::invalid_argument("Invalid arguments!");
            }

            Point center(std::stod(arguments[1]),std::stod(arguments[2]));
            unsigned radius = std::stoi(arguments[3]);
            short startAngle = std::stoi(arguments[4]);
            short arcWidth = std::stoi(arguments[5]);
            Color fill = Color::stringToColor(arguments[6]);
            Color border = Color::stringToColor(arguments[7]);

            Arc* arc = new Arc();
            arc->setPoint(0, center.x, center.y);
            arc->setRadius(radius);
            arc->setStartAngle(startAngle);
            arc->setArcWidth(arcWidth);
            arc->setFillColor(fill.redValue, fill.greenValue, fill.blueValue, fill.alpha);
            arc->setBorderColor(border.redValue, border.greenValue, border.blueValue, border.alpha);

            return arc;
        }
        else if (arguments[0] == "line")
        {
            if(arguments.size() != 7)
            {
                throw std::invalid_argument("Invalid arguments!");
            }

            Point start(std::stod(arguments[1]),std::stod(arguments[2]));
            Point end(std::stod(arguments[3]),std::stod(arguments[4]));
            Color fill = Color::stringToColor(arguments[5]);
            Color border = Color::stringToColor(arguments[6]);

            Line* line = new Line();
            line->setPoint(0, start.x, start.y);
            line->setPoint(1, end.x, end.y);
            line->setFillColor(fill.redValue, fill.greenValue, fill.blueValue, fill.alpha);
            line->setBorderColor(border.redValue, border.greenValue, border.blueValue, border.alpha);

            return line;
        }
        else if (arguments[0] == "polygon")
        {
            unsigned coordinateInputs = arguments.size() - 3; // -3 because of the type, fill and border color

            Polygon* polygon = new Polygon(coordinateInputs/2);
            try
            {
                for (int i = 1,j = 0; i < coordinateInputs; i+=2, j++)
                {

                    polygon->setPoint(j, std::stod(arguments[i]), std::stod(arguments[i+1]));


                }
                Color fill = Color::stringToColor(arguments[coordinateInputs+1]);
                Color border = Color::stringToColor(arguments[coordinateInputs+2]);

                polygon->setFillColor(fill.redValue, fill.greenValue, fill.blueValue, fill.alpha);
                polygon->setBorderColor(border.redValue, border.greenValue, border.blueValue, border.alpha);

                return polygon;
            }
            catch(const std::invalid_argument& e)
            {
                delete polygon;
                throw e;
            }
        }
        else if (arguments[0] == "rectangle")
        {
            if(arguments.size() != 7)
            {
                throw std::invalid_argument("Invalid arguments!");
            }

            Point topLeft(std::stod(arguments[1]),std::stod(arguments[2]));
            unsigned width = std::stoi(arguments[3]);
            unsigned height = std::stoi(arguments[4]);
            Color fill = Color::stringToColor(arguments[5]);
            Color border = Color::stringToColor(arguments[6]);

            Rectangle* rectangle = new Rectangle();
            rectangle->setPoint(0, topLeft.x, topLeft.y);
            rectangle->setWidth(width);
            rectangle->setHeight(height);
            rectangle->setFillColor(fill.redValue, fill.greenValue, fill.blueValue, fill.alpha);
            rectangle->setBorderColor(border.redValue, border.greenValue, border.blueValue, border.alpha);

            return rectangle;
        }
        else
        {
            throw std::invalid_argument("Invalid shape type.");
        }
    } catch (std::invalid_argument& e)
    {
        throw e;
    }
}

std::string ShapeFactory::getShapeAsSVG(Shape& shape)
{
    std::string shapeArgs = shape.extract();
    std::vector<std::string> arguments = splitString(shapeArgs);

    std::string svg = "";

    if(arguments[0] == "arc")
    {
        //get the start and end point of the arc
        short arcStartAngle = std::stoi(arguments[4]);
        short arcEndAngle = arcStartAngle + std::stoi(arguments[5]);
        bool flip = 180 < arcEndAngle;
        Point startPoint = Arc::getPointByAngle(std::stod(arguments[1]), std::stod(arguments[2]), std::stoi(arguments[3]), arcStartAngle);
        Point endPoint = Arc::getPointByAngle(std::stod(arguments[1]), std::stod(arguments[2]), std::stoi(arguments[3]), arcEndAngle);

        svg += "<path d=\"M " + std::to_string(startPoint.x) + " " + std::to_string(startPoint.y) +
                " A " + arguments[3] + " " + arguments[3] + ", 0," + std::to_string(flip) + " " + std::to_string(flip) + ", " + std::to_string(endPoint.x) + " " + std::to_string(endPoint.y) +
                " L " + arguments[1] + " " + arguments[2] +
                " L " + std::to_string(startPoint.x) + " " + std::to_string(startPoint.y) +
                "\" fill=\"" + arguments[6] + "\" stroke=\"" + arguments[7] + "\"/>\n";
    }
    else if(arguments[0] == "line")
    {
        svg += "<line x1=\"" + arguments[1] + "\" y1=\"" + arguments[2] + "\" x2=\"" + arguments[3] + "\" y2=\"" + arguments[4] + "\" stroke=\"" + arguments[6] + "\" stroke-width=\"2\"/>\n";
    }
    else if(arguments[0] == "polygon")
    {
        unsigned pointsCount = arguments.size() - 3;
        svg += "<polygon points=\"";
        for (int i = 1; i < pointsCount; i+=2)
        {
            svg += arguments[i] + "," + arguments[i+1] + " ";
        }
        svg += "\" fill=\"" + arguments[pointsCount+1] + "\" stroke=\"" + arguments[pointsCount+2] + "\"/>\n";
    }
    else if(arguments[0] == "rectangle")
    {
        svg+= "<rect x=\"" + arguments[1] + "\" y=\"" + arguments[2] + "\" width=\"" + arguments[3] + "\" height=\"" + arguments[4] + "\" fill=\"" + arguments[5] + "\" stroke=\"" + arguments[6] + "\"/>\n";
    }

    return svg;
}