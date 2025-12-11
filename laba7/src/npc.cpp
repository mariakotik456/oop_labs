#include "../include/npc.h"
#include <cmath>
#include <random>

NPC::NPC(const std::string &name, int x, int y, int move_dist, int kill_dist)
    : name(name), x(x), y(y), alive(true), move_distance(move_dist), kill_distance(kill_dist) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
bool NPC::isAlive() const { return alive; }
void NPC::setAlive(bool alive) { this->alive = alive; }
int NPC::getMoveDistance() const { return move_distance; }
int NPC::getKillDistance() const { return kill_distance; }

double NPC::distanceTo(const NPC &other) const
{
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

bool NPC::canKill(const NPC &other) const
{
    return distanceTo(other) <= kill_distance;
}

void NPC::move(int max_x, int max_y)
{
    if (!alive)
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-move_distance, move_distance);

    int new_x = x + dist(gen);
    int new_y = y + dist(gen);

    x = std::max(0, std::min(new_x, max_x - 1));
    y = std::max(0, std::min(new_y, max_y - 1));
}

int NPC::rollDice() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}