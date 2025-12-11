#include "../include/observer.h"
#include <iostream>
#include <fstream>

void ConsoleObserver::onBattleResult(const std::string &killer,
                                     const std::string &victim,
                                     const std::string &result)
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << result << std::endl;
}

FileObserver::FileObserver(const std::string &filename) : filename(filename) {}

void FileObserver::onBattleResult(const std::string &killer,
                                  const std::string &victim,
                                  const std::string &result)
{
    std::lock_guard<std::mutex> lock(file_mutex);
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        file << result << std::endl;
        file.close();
    }
}