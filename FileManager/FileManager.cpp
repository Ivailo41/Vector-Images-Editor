#include "FileManager.h"
#include "../CommandListener/CommandListener.h"
#include "../Canvas/Canvas.h"
#include "../ShapeFactory/ShapeFactory.h"

void FileManager::open(const std::string &fileName)
{
    std::string extension = getFileExtension(fileName);

    if (extension == "txt")
    {
        openTXT(fileName);
    } else if (extension == "svg")
    {
        openSVG(fileName);
    } else
    {
        std::cout << "Invalid file extension!\n";
    }
}

bool FileManager::save(const std::string &fileName)
{
    std::string extension = getFileExtension(fileName);

    if (extension == "txt")
    {
        return saveTXT(fileName);
    } else if (extension == "svg")
    {
        return saveSVG(fileName);
    } else
    {
        std::cout << "Invalid file extension!\n";
        return false;
    }
}

void FileManager::openTXT(const std::string &fileName)
{
    std::cout << "Opening TXT file " << fileName << "\n";
    std::fstream file(fileName, std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("File could not be opened!");
    }

    std::vector<std::string> fileContent;
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        fileContent.push_back(line);
    }
    if (file.bad())
    {
        file.close();
        throw std::runtime_error("File could not be read!");
    }
    file.close();

    unsigned shapesCount = fileContent.size();
    for (int i = 0; i < shapesCount; ++i)
    {
        std::vector<std::string> inputs;
        inputs.emplace_back("create");
        std::vector<std::string> temp = splitString(fileContent[i]);
        inputs.insert(inputs.end(), temp.begin(), temp.end());
        try
        {
            CommandListener::getInstance().executeCommand(inputs);
        } catch (const std::exception &e)
        {
            std::cout << "Invalid arguments in file" << '\n';
        }
    }
}

void FileManager::openSVG(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::in);
    std::vector<std::string> shapes;
    if (!file.is_open())
    {
        throw std::runtime_error("File could not be opened!");
    }
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        shapes.push_back(line);
    }
    if (file.bad())
    {
        file.close();
        throw std::runtime_error("File could not be read!");
    }
    file.close();

    unsigned shapesCount = shapes.size();
    for (int i = 0; i < shapesCount; ++i)
    {
        std::string line = shapes[i];
        std::vector<std::string> inputs;
        if (line.find("line") != std::string::npos)
        {
            inputs.emplace_back("create");
            inputs.push_back("line");
            inputs.push_back(line.substr(line.find("x1=") + 4, line.find("y1=") - line.find("x1=") - 5));
            inputs.push_back(line.substr(line.find("y1=") + 4, line.find("x2=") - line.find("y1=") - 5));
            inputs.push_back(line.substr(line.find("x2=") + 4, line.find("y2=") - line.find("x2=") - 5));
            inputs.push_back(line.substr(line.find("y2=") + 4, line.find("stroke=") - line.find("y2=") - 6));
            inputs.push_back(
                    line.substr(line.find("stroke=") + 8, line.find("stroke-width=") - line.find("stroke=") - 10));
            inputs.push_back(
                    line.substr(line.find("stroke=") + 8, line.find("stroke-width=") - line.find("stroke=") - 10));
        }
        else if (line.find("rect") != std::string::npos)
        {
            inputs.emplace_back("create");
            inputs.push_back("rectangle");

            unsigned position = line.find_first_of('\"', line.find("x=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("y=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("width=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("height=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("fill=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("stroke=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));
        }
        else if (line.find("path") != std::string::npos)
        {
            inputs.emplace_back("create");
            inputs.push_back("arc");

            //get center x and y
            unsigned position = line.find("L") + 2;
            inputs.push_back(line.substr(position, line.find_first_of(' ', position) - position));

            position = line.find_first_of(' ', position) + 1;
            inputs.push_back(line.substr(position, line.find_first_of(' ', position) - position));

            //radius
            position = line.find("A") + 2;
            inputs.push_back(line.substr(position, line.find_first_of(' ', position) - position));

            //Start point
            position = line.find("M") + 2;
            double startPointX = std::stod((line.substr(position, line.find_first_of(' ', position) - position)));

            position = line.find_first_of(' ', position) + 1;
            double startPointY = std::stod((line.substr(position, line.find_first_of(' ', position) - position)));

            //End point
            position = line.find_first_of(',', 0) + 9;
            double endPointX = std::stod((line.substr(position, line.find_first_of(' ', position) - position)));

            position = line.find_first_of(' ', position) + 1;
            double endPointY = std::stod((line.substr(position, line.find_first_of(' ', position) - position)));

            //variables to calculate start angle and the angle width
            Point center(std::stod(inputs[2]), std::stod(inputs[3]));
            Point startPoint(startPointX, startPointY);
            Point endPoint(endPointX, endPointY);
            double radius = std::stod(inputs[4]);
            bool flipped = (bool)line[line.find_first_of(',', 0) + 4];

            double startAngle = Point::getAngleBetweenPoints(center, startPoint, Point(center.x + radius, center.y));
            double angleWidth = Point::getAngleBetweenPoints(center, startPoint, endPoint);

            if(flipped)
            {
                angleWidth = 360 - angleWidth;
            }

            inputs.push_back(std::to_string(startAngle));
            inputs.push_back(std::to_string(angleWidth));

            position = line.find_first_of('\"', line.find("fill=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("stroke=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));
        }
        else if (line.find("polygon") != std::string::npos)
        {
            inputs.emplace_back("create");
            inputs.push_back("polygon");

            unsigned position = line.find_first_of('\"', line.find("points=")) + 1;
            std::vector<std::string> points = splitString(line.substr(position, line.find_first_of('\"', position) - position - 1));

            unsigned pointsCount = points.size();
            for (int i = 0; i < pointsCount; ++i)
            {
                inputs.push_back(points[i].substr(0, points[i].find(',')));
                inputs.push_back(points[i].substr(points[i].find(',') + 1, points[i].size() - points[i].find(',') - 1));
            }

            position = line.find_first_of('\"', line.find("fill=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));

            position = line.find_first_of('\"', line.find("stroke=")) + 1;
            inputs.push_back(line.substr(position, line.find_first_of('\"', position) - position));
        }
        else
        {
            continue;
        }
        try
        {
            CommandListener::getInstance().executeCommand(inputs);
        } catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }
}

bool FileManager::saveTXT(const std::string &fileName)
{
    std::ofstream file(fileName, std::ios::out);
    if (!file.is_open())
    {
        throw std::runtime_error("File could not be opened!");
    }

    unsigned shapesCount = Canvas::getInstance().getShapesCount();
    for (int i = 0; i < shapesCount; ++i)
    {
        std::string line = Canvas::getInstance().getShapeAt(i).extract();
        file << line;
        if (i != shapesCount - 1)
        {
            file << "\n";
        }
    }
    file.close();
    return true;
}

bool FileManager::saveSVG(const std::string &fileName)
{
    Point canvasSize = Canvas::getInstance().getCanvasSize();
    std::vector<std::string> shapesInSVG;
    unsigned shapesCount = Canvas::getInstance().getShapesCount();
    for (int i = 0; i < shapesCount; ++i)
    {
        shapesInSVG.push_back(ShapeFactory::getShapeAsSVG(Canvas::getInstance().getShapeAt(i)));
    }

    std::ofstream file(fileName, std::ios::out);
    if (!file.is_open())
    {
        throw std::runtime_error("File could not be opened!");
    }
    file << "<svg width=\"" + std::to_string(canvasSize.x) + "\" height=\"" + std::to_string(canvasSize.y) + "\">\n";
    for (int i = 0; i < shapesCount; ++i)
    {
        file << shapesInSVG[i];
    }
    file << "</svg>";
    file.close();
}

std::string getFileExtension(const std::string &fileName)
{
    unsigned start = fileName.find_last_of('.');
    return fileName.substr(start + 1);
}