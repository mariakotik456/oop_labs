#include "../include/game_engine.h"
#include <iostream>
#include <chrono>
#include <thread>

GameEngine::GameEngine() : game_running(false)
{
    battleManager = std::make_shared<BattleManager>();
    battleManager->addObserver(std::make_shared<ConsoleObserver>());
    battleManager->addObserver(std::make_shared<FileObserver>());
}

GameEngine::~GameEngine()
{
    stop();
}

void GameEngine::initialize()
{
    std::lock_guard<std::shared_mutex> lock(npc_mutex);

    for (int i = 0; i < 50; ++i)
    {
        auto npc = NPCFactory::createRandomNPC("NPC_" + std::to_string(i + 1), MAP_SIZE, MAP_SIZE);
        if (npc)
        {
            npcs.push_back(npc);
        }
    }

    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Инициализировано " << npcs.size() << " NPC на карте " << MAP_SIZE << "x" << MAP_SIZE << std::endl;
    }
}

void GameEngine::run()
{
    game_running = true;

    movement_thread = std::thread(&GameEngine::movement_worker, this);
    battle_thread = std::thread(&GameEngine::battle_worker, this);
    print_thread = std::thread(&GameEngine::print_worker, this);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));

    stop();
    printSurvivors();
}

void GameEngine::stop()
{
    game_running = false;

    if (movement_thread.joinable())
        movement_thread.join();
    if (battle_thread.joinable())
        battle_thread.join();
    if (print_thread.joinable())
        print_thread.join();
}

void GameEngine::movement_worker()
{
    while (game_running)
    {
        {
            std::shared_lock<std::shared_mutex> lock(npc_mutex);

            for (auto &npc : npcs)
            {
                if (npc->isAlive())
                {
                    npc->move(MAP_SIZE, MAP_SIZE);
                }
            }

            for (size_t i = 0; i < npcs.size(); ++i)
            {
                if (!npcs[i]->isAlive())
                    continue;

                for (size_t j = i + 1; j < npcs.size(); ++j)
                {
                    if (!npcs[j]->isAlive())
                        continue;

                    if (npcs[i]->canKill(*npcs[j]) || npcs[j]->canKill(*npcs[i]))
                    {
                        BattleVisitor visitor(battleManager.get(), npcs[i]);
                        npcs[j]->accept(visitor);
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameEngine::battle_worker()
{
    while (game_running)
    {
        while (battleManager->hasBattleTasks())
        {
            BattleTask task = battleManager->getBattleTask();
            if (task.attacker && task.defender)
            {
                battleManager->performBattle(task.attacker, task.defender);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void GameEngine::print_worker()
{
    while (game_running)
    {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void GameEngine::printMap()
{
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "\n=== КАРТА ===" << std::endl;

    std::vector<std::vector<char>> map(MAP_SIZE, std::vector<char>(MAP_SIZE, '.'));

    {
        std::shared_lock<std::shared_mutex> lock(npc_mutex);

        for (const auto &npc : npcs)
        {
            if (npc->isAlive())
            {
                int x = npc->getX();
                int y = npc->getY();

                char symbol = '.';
                if (npc->getType() == "Orc")
                    symbol = 'O';
                else if (npc->getType() == "Bear")
                    symbol = 'B';
                else if (npc->getType() == "Squirrel")
                    symbol = 'S';

                if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
                {
                    map[y][x] = symbol;
                }
            }
        }
    }

    for (int y = 0; y < MAP_SIZE; ++y)
    {
        for (int x = 0; x < MAP_SIZE; ++x)
        {
            std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "O-Орк, B-Медведь, S-Белка, .-пусто" << std::endl;
}

void GameEngine::printSurvivors()
{
    std::shared_lock<std::shared_mutex> lock(npc_mutex);
    std::lock_guard<std::mutex> cout_lock(cout_mutex);

    std::cout << "\n=== ВЫЖИВШИЕ NPC ===" << std::endl;
    int survivor_count = 0;

    for (const auto &npc : npcs)
    {
        if (npc->isAlive())
        {
            std::cout << npc->getType() << " " << npc->getName()
                      << " в (" << npc->getX() << "," << npc->getY() << ")" << std::endl;
            survivor_count++;
        }
    }

    std::cout << "Всего выжило: " << survivor_count << " NPC" << std::endl;
}