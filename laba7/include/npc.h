#pragma once
#include <string>
#include <memory>
#include <random>

class NPCVisitor;

class NPC {
protected:
    std::string name;
    int x, y;
    bool alive;
    int move_distance;
    int kill_distance;

public:
    NPC(const std::string &name, int x, int y, int move_dist, int kill_dist);
    virtual ~NPC() = default;

    virtual void accept(NPCVisitor &visitor) = 0;
    virtual std::string getType() const = 0;

    std::string getName() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    void setAlive(bool alive);
    
    double distanceTo(const NPC &other) const;
    bool canKill(const NPC &other) const;
    void move(int max_x, int max_y);
    
    int rollDice() const;
    int getMoveDistance() const;
    int getKillDistance() const;
};