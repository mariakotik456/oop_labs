#pragma once
#include "npc.h"
#include <memory>

class Orc : public NPC, public std::enable_shared_from_this<Orc>
{
public:
    Orc(const std::string &name, int x, int y);
    void accept(NPCVisitor &visitor) override;
    std::string getType() const override;
};

class Bear : public NPC, public std::enable_shared_from_this<Bear>
{
public:
    Bear(const std::string &name, int x, int y);
    void accept(NPCVisitor &visitor) override;
    std::string getType() const override;
};

class Squirrel : public NPC, public std::enable_shared_from_this<Squirrel>
{
public:
    Squirrel(const std::string &name, int x, int y);
    void accept(NPCVisitor &visitor) override;
    std::string getType() const override;
};