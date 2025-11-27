#include "../include/observer.h"
#include <iostream>
#include <fstream>

void ConsoleObserver::onBattleResult(const std::string &killer,
                                     const std::string &victim,
                                     const std::string &result)
{
    std::cout << result << std::endl;
}

FileObserver::FileObserver(const std::string &filename) : filename(filename) {}

void FileObserver::onBattleResult(const std::string &killer,
                                  const std::string &victim,
                                  const std::string &result)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        file << result << std::endl;
        file.close();
    }
}