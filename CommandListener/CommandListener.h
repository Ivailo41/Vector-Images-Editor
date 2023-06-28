#ifndef SVG_PROJECT_COMMANDLISTENER_H
#define SVG_PROJECT_COMMANDLISTENER_H

#include<string>
#include <vector>
#include <iostream>

enum class Commands
        {
                OPEN,
                PRINT,
                CREATE,
                GROUP,
                UNGROUP,
                INSERT,
                EXTRACT,
                HIDE,
                SHOW,
                TRANSLATE,
                SCALE,
                SAVE,
                SAVEAS,
                HELP,
                EXIT,
                COUNT
        };

//Singleton
class CommandListener
{
public:
    static CommandListener& getInstance();
    void listen() const;
    bool executeCommand(std::vector<std::string> inputs) const;

private:
    CommandListener() = default;
    CommandListener(const CommandListener& other) = delete;
    CommandListener& operator=(const CommandListener& other) = delete;
    ~CommandListener() = default;

private:
    static CommandListener commandListener;
    static const std::vector<std::string> commands;

};

std::vector<std::string> splitString(const std::string& line);


#endif //SVG_PROJECT_COMMANDLISTENER_H
