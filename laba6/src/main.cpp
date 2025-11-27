#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "../include/npc_factory.h"
#include "../include/battle_visitor.h"
#include "../include/observer.h"

class DungeonEditor
{
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::shared_ptr<BattleManager> battleManager;

public:
    DungeonEditor() : battleManager(std::make_shared<BattleManager>(50.0))
    {
        // Добавляем наблюдателей
        battleManager->addObserver(std::make_shared<ConsoleObserver>());
        battleManager->addObserver(std::make_shared<FileObserver>());
    }

    void addNPC(const std::string &type, const std::string &name, int x, int y)
    {
        if (x <= 0 || x > 500 || y <= 0 || y > 500)
        {
            std::cout << "Координаты должны быть в диапазоне 0 < x,y <= 500" << std::endl;
            return;
        }

        auto npc = NPCFactory::createNPC(type, name, x, y);
        if (npc)
        {
            npcs.push_back(npc);
            std::cout << "Добавлен " << type << " " << name << " в (" << x << "," << y << ")" << std::endl;
        }
    }

    void printNPCs()
    {
        std::cout << "\n=== Список NPC ===" << std::endl;
        for (const auto &npc : npcs)
        {
            if (npc->isAlive)
            {
                std::cout << npc->getType() << " " << npc->getName()
                          << " в (" << npc->getX() << "," << npc->getY() << ")" << std::endl;
            }
        }
    }

    void saveToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &npc : npcs)
            {
                if (npc->isAlive)
                {
                    file << NPCFactory::saveToString(*npc) << std::endl;
                }
            }
            file.close();
            std::cout << "Сохранено в " << filename << std::endl;
        }
    }

    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            npcs.clear();
            std::string line;
            while (std::getline(file, line))
            {
                auto npc = NPCFactory::loadFromString(line);
                if (npc)
                {
                    npcs.push_back(npc);
                }
            }
            file.close();
            std::cout << "Загружено из " << filename << std::endl;
        }
    }

    void startBattle(double range)
    {
        std::cout << "\n=== НАЧАЛО БИТВЫ (дистанция: " << range << ") ===" << std::endl;
        battleManager = std::make_shared<BattleManager>(range);
        battleManager->addObserver(std::make_shared<ConsoleObserver>());
        battleManager->addObserver(std::make_shared<FileObserver>());

        battleManager->fightCycle(npcs);

        std::cout << "=== КОНЕЦ БИТВЫ ===" << std::endl;
    }
};

int main()
{
    DungeonEditor editor;
    int choice;

    do
    {
        std::cout << "\n=== Редактор подземелья Balagur Fate 3 ===" << std::endl;
        std::cout << "1. Добавить NPC" << std::endl;
        std::cout << "2. Показать всех NPC" << std::endl;
        std::cout << "3. Сохранить в файл" << std::endl;
        std::cout << "4. Загрузить из файла" << std::endl;
        std::cout << "5. Начать битву" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string type, name;
            int x, y;

            std::cout << "Тип (Orc/Bear/Squirrel): ";
            std::cin >> type;
            std::cout << "Имя: ";
            std::cin >> name;
            std::cout << "X координата: ";
            std::cin >> x;
            std::cout << "Y координата: ";
            std::cin >> y;

            editor.addNPC(type, name, x, y);
            break;
        }
        case 2:
            editor.printNPCs();
            break;
        case 3:
            editor.saveToFile("dungeon.txt");
            break;
        case 4:
            editor.loadFromFile("dungeon.txt");
            break;
        case 5:
        {
            double range;
            std::cout << "Дистанция боя: ";
            std::cin >> range;
            editor.startBattle(range);
            break;
        }
        }
    } while (choice != 0);

    return 0;
}