#pragma once
#include <string>
#include <memory>
#include <mutex>

class BattleObserver
{
public:
    virtual ~BattleObserver() = default;
    virtual void onBattleResult(const std::string &killer,
                                const std::string &victim,
                                const std::string &result) = 0;
};

class ConsoleObserver : public BattleObserver
{
private:
    std::mutex cout_mutex;

public:
    void onBattleResult(const std::string &killer,
                        const std::string &victim,
                        const std::string &result) override;
};

class FileObserver : public BattleObserver
{
private:
    std::string filename;
    std::mutex file_mutex;

public:
    FileObserver(const std::string &filename = "log.txt");
    void onBattleResult(const std::string &killer,
                        const std::string &victim,
                        const std::string &result) override;
};