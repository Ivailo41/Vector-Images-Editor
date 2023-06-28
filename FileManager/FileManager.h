#ifndef SVG_PROJECT_FILEMANAGER_H
#define SVG_PROJECT_FILEMANAGER_H
#include <string>
#include <fstream>

class FileManager
{
public:
    static void open(const std::string& fileName);
    static bool save(const std::string& fileName);


private:
    FileManager() = default;
    FileManager(const FileManager& other) = delete;
    FileManager& operator=(const FileManager& other) = delete;
    ~FileManager() = default;

    static void openTXT(const std::string& fileName);
    static void openSVG(const std::string& fileName);

    static bool saveTXT(const std::string& fileName);
    static bool saveSVG(const std::string& fileName);

private:
    static FileManager fileManager;
};

std::string getFileExtension(const std::string& fileName);

#endif //SVG_PROJECT_FILEMANAGER_H
