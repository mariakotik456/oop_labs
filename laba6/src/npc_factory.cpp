#include "../include/npc_factory.h"
#include <sstream>

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