#pragma once
#include <string>
#include <memory>

class NPCVisitor;

class NPC
{
protected:
    std::string name;
    int x, y;

public:
    NPC(const std::string &name, int x, int y);
    virtual ~NPC() = default;

    virtual void accept(NPCVisitor &visitor) = 0;
    virtual std::string getType() const = 0;

    std::string getName() const;
    int getX() const;
    int getY() const;

    double distanceTo(const NPC &other) const;
    bool isAlive;
};