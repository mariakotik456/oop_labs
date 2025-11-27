#include "../include/battle_visitor.h"
#include <iostream>
#include <algorithm>

BattleManager::BattleManager(double range) : battleRange(range) {}

void BattleManager::addObserver(std::shared_ptr<BattleObserver> observer)
{
    observers.push_back(observer);
}

void BattleManager::removeObserver(std::shared_ptr<BattleObserver> observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

void BattleManager::notifyObservers(const std::string &killer,
                                    const std::string &victim,
                                    const std::string &result)
{
    for (auto &observer : observers)
    {
        observer->onBattleResult(killer, victim, result);
    }
}

void BattleManager::battle(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
{
    if (!attacker->isAlive || !defender->isAlive)
        return;

    if (attacker->distanceTo(*defender) > battleRange)
        return;

    std::string attackerType = attacker->getType();
    std::string defenderType = defender->getType();

    if (attackerType == "Orc")
    {
        if (defenderType == "Bear" || defenderType == "Squirrel" || defenderType == "Orc")
        {
            defender->isAlive = false;
            std::string result = attacker->getName() + " убил " + defender->getName();
            notifyObservers(attacker->getName(), defender->getName(), result);
        }
    }
    else if (attackerType == "Bear")
    {
        if (defenderType == "Squirrel")
        {
            defender->isAlive = false;
            std::string result = attacker->getName() + " убил " + defender->getName();
            notifyObservers(attacker->getName(), defender->getName(), result);
        }
    }
}

void BattleManager::fightCycle(std::vector<std::shared_ptr<NPC>> &npcs)
{
    for (size_t i = 0; i < npcs.size(); ++i)
    {
        if (!npcs[i]->isAlive)
            continue;

        for (size_t j = i + 1; j < npcs.size(); ++j)
        {
            if (!npcs[j]->isAlive)
                continue;

            BattleVisitor visitor1(this, npcs[i]);
            npcs[j]->accept(visitor1);

            BattleVisitor visitor2(this, npcs[j]);
            npcs[i]->accept(visitor2);
        }
    }

    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
                              [](const std::shared_ptr<NPC> &npc)
                              {
                                  return !npc->isAlive;
                              }),
               npcs.end());
}

NPCVisitor::NPCVisitor(BattleManager *manager, std::shared_ptr<NPC> npc)
    : battleManager(manager), currentNPC(npc) {}

void BattleVisitor::visit(std::shared_ptr<Orc> orc)
{
    battleManager->battle(currentNPC, orc);
}

void BattleVisitor::visit(std::shared_ptr<Bear> bear)
{
    battleManager->battle(currentNPC, bear);
}

void BattleVisitor::visit(std::shared_ptr<Squirrel> squirrel)
{
    battleManager->battle(currentNPC, squirrel);
}