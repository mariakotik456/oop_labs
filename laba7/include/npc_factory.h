#pragma once
#include "types.h"
#include <memory>
#include <string>

class NPCFactory
{
public:
    static std::shared_ptr<NPC> createNPC(const std::string &type,
                                          const std::string &name,
                                          int x, int y);

    static std::shared_ptr<NPC> createRandomNPC(const std::string &name, int max_x, int max_y);
    static std::shared_ptr<NPC> loadFromString(const std::string &data);
    static std::string saveToString(const NPC &npc);
};