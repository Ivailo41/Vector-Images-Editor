#include "CommandListener.h"
#include "../Canvas/Canvas.h"
#include "../ShapeFactory/ShapeFactory.h"
#include "../FileManager/FileManager.h"

const std::vector<std::string> CommandListener::commands = {"open", "print", "create", "group", "ungroup", "insert", "extract",
                                              "hide", "show", "translate", "scale", "save", "saveas", "help", "exit"};

CommandListener CommandListener::commandListener;

CommandListener& CommandListener::getInstance()
{
    return commandListener;
}

void CommandListener::listen() const
{
    bool shouldExit = false;

    while(!shouldExit)
    {
        std::string line;
        std::cout << "Enter command: ";
        std::getline(std::cin, line);

        std::vector<std::string> inputs = splitString(line);

        try
        {
            shouldExit = executeCommand(inputs);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
}

std::vector<std::string> splitString(const std::string& line)
{
    std::vector<std::string> inputs;
    std::string input;

    for (int i = 0; i < line.size(); ++i)
    {
        if(line[i] == ' ')
        {
            inputs.push_back(input);
            input.clear();
        }
        else
        {
            input += line[i];
        }
    }
    inputs.push_back(input);

    return inputs;
}

bool CommandListener::executeCommand(std::vector<std::string> inputs) const
{
    try
    {
        if(inputs[0] == commands[(int)Commands::OPEN])
        {
            if(inputs.size() != 2)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }

            if(!Canvas::getInstance().isCanvasEmpty())
            {
                std::cout << "Canvas is not empty, do you want to save?\n";
                bool save;
                std::cin >> save;
                if(save)
                {
                    FileManager::save(Canvas::getInstance().currentFileName);
                }
                Canvas::getInstance().clearCanvas();
            }

            FileManager::open(inputs[1]);
            Canvas::getInstance().currentFileName = inputs[1];
        }
        else if(inputs[0] == commands[(int)Commands::PRINT])
        {
            Canvas::getInstance().print();
            return false;
        }
        else if(inputs[0] == commands[(int)Commands::CREATE])
        {
            inputs.erase(inputs.begin());
            Shape* shape = ShapeFactory::getInstance().createShape(inputs);
            Canvas::getInstance().addShape(*shape);
        }
        else if(inputs[0] == commands[(int)Commands::GROUP])
        {
            if(inputs.size() != 5)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }

            double topLeftX = std::stod(inputs[1]);
            double topLeftY = std::stod(inputs[2]);
            double bottomRightX = std::stod(inputs[3]);
            double bottomRightY = std::stod(inputs[4]);

            Canvas::getInstance().group(topLeftX, topLeftY, bottomRightX, bottomRightY);
        }
        else if(inputs[0] == commands[(int)Commands::UNGROUP])
        {
            if(inputs.size() != 2)
            {
                std::cout << "Invalid arguments!\n";
                 return false;
            }

            unsigned id = std::stoi(inputs[1]);
            Canvas::getInstance().ungroup(id);
        }
        else if(inputs[0] == commands[(int)Commands::INSERT])
        {
            if(inputs.size() != 3)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }

            unsigned id = std::stoi(inputs[1]);
            unsigned groupId = std::stoi(inputs[2]);
            Canvas::getInstance().insertShapeInGroup(id, groupId);

        }
        else if(inputs[0] == commands[(int)Commands::EXTRACT])
        {
            if(inputs.size() != 3)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }

            unsigned id = std::stoi(inputs[1]);
            unsigned groupId = std::stoi(inputs[2]);
            Canvas::getInstance().extractShapeFromGroup(id, groupId);
        }
        else if(inputs[0] == commands[(int)Commands::HIDE])
        {
            if(inputs.size() != 2)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }
            unsigned id = std::stoi(inputs[1]);
            Canvas::getInstance().hideShape(id);
        }
        else if(inputs[0] == commands[(int)Commands::SHOW])
        {
            if(inputs.size() != 2)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }
            unsigned id = std::stoi(inputs[1]);
            Canvas::getInstance().showShape(id);
        }
        else if(inputs[0] == commands[(int)Commands::TRANSLATE])
        {
            if(inputs.size() == 3)
            {

                double horizontal = std::stod(inputs[1]);
                double vertical = std::stod(inputs[2]);

                Canvas::getInstance().translate(horizontal, vertical);
            }
            else if(inputs.size() == 4)
            {

                unsigned id = std::stoi(inputs[1]);
                unsigned horizontal = std::stoi(inputs[2]);
                unsigned vertical = std::stoi(inputs[3]);

                Canvas::getInstance().translate(id, horizontal, vertical);
            }
            else
            {
                std::cout << "Invalid arguments!\n";
            }
        }
        else if(inputs[0] == commands[(int)Commands::SCALE])
        {
            if(inputs.size() == 3)
            {
                double horizontal = std::stod(inputs[1]);
                double vertical = std::stod(inputs[2]);

                Canvas::getInstance().scale(horizontal, vertical);
            }
            else if(inputs.size() == 4)
            {
                unsigned id = std::stoi(inputs[1]);
                unsigned horizontal = std::stoi(inputs[2]);
                unsigned vertical = std::stoi(inputs[3]);

                Canvas::getInstance().scale(id, horizontal, vertical);
            }
            else
            {
                std::cout << "Invalid arguments!\n";
            }
        }
        else if(inputs[0] == commands[(int)Commands::SAVE])
        {
            if(inputs.size() != 1)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }

            std::string fileName = Canvas::getInstance().currentFileName;

            if(fileName.empty())
            {
                std::cout << "Enter file name: ";
                std::cin >> fileName;

            }

            if(FileManager::save(fileName))
                Canvas::getInstance().currentFileName = fileName;
        }
        else if(inputs[0] == commands[(int)Commands::SAVEAS])
        {
            if(inputs.size() != 2)
            {
                std::cout << "Invalid arguments!\n";
                return false;
            }
            FileManager::save(inputs[1]);
            Canvas::getInstance().currentFileName = inputs[1];
        }
        else if(inputs[0] == commands[(int)Commands::HELP])
        {
            std::cout << "Available Commands:\n";
            for (int i = 0; i < (int)Commands::COUNT; ++i)
            {
                std::cout << commands[i] << std::endl;
            }
        }
        else if(inputs[0] == commands[(int)Commands::EXIT])
        {
            Canvas::getInstance().clearCanvas();
            return true;
        }
        else
        {
            std::cout << "Invalid command!\n";
        }
        return false;
    }
    catch (std::exception& e)
    {
        throw;
    }
}