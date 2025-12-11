#include "../include/game_engine.h"
#include <iostream>

int main()
{
    try
    {
        GameEngine game;

        std::cout << "=== ЗАПУСК ИГРЫ ===" << std::endl;
        std::cout << "Длительность: 30 секунд" << std::endl;
        std::cout << "Размер карты: 100x100" << std::endl;
        std::cout << "Количество NPC: 50" << std::endl;
        std::cout << "==================" << std::endl;

        game.initialize();

        game.run();

        std::cout << "=== ИГРА ЗАВЕРШЕНА ===" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}