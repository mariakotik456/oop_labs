#pragma once
#include "npc_factory.h"
#include "battle_visitor.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <chrono>

class GameEngine
{
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::shared_ptr<BattleManager> battleManager;

    std::thread movement_thread;
    std::thread battle_thread;
    std::thread print_thread;

    std::shared_mutex npc_mutex;
    std::mutex cout_mutex;

    std::atomic<bool> game_running;
    const int MAP_SIZE = 100;
    const int GAME_DURATION = 30;

public:
    GameEngine();
    ~GameEngine();

    void initialize();
    void run();
    void stop();

private:
    void movement_worker();
    void battle_worker();
    void print_worker();
    void printMap();
    void printSurvivors();
};