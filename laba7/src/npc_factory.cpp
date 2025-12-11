#include "../include/npc_factory.h"
#include <sstream>
#include <random>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string &type,
                                           const std::string &name,
                                           int x, int y)
{
    if (type == "Orc")
        return std::make_shared<Orc>(name, x, y);
    if (type == "Bear")
        return std::make_shared<Bear>(name, x, y);
    if (type == "Squirrel")
        return std::make_shared<Squirrel>(name, x, y);
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::createRandomNPC(const std::string &name, int max_x, int max_y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 2);
    std::uniform_int_distribution<> coord_dist(0, max_x - 1);

    std::string types[] = {"Orc", "Bear", "Squirrel"};
    std::string type = types[type_dist(gen)];
    int x = coord_dist(gen);
    int y = coord_dist(gen);

    return createNPC(type, name, x, y);
}

std::shared_ptr<NPC> NPCFactory::loadFromString(const std::string &data)
{
    std::istringstream iss(data);
    std::string type, name;
    int x, y;

    if (iss >> type >> name >> x >> y)
    {
        return createNPC(type, name, x, y);
    }
    return nullptr;
}

std::string NPCFactory::saveToString(const NPC &npc)
{
    std::ostringstream oss;
    oss << npc.getType() << " " << npc.getName() << " "
        << npc.getX() << " " << npc.getY();
    return oss.str();
}