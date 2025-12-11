#include "../include/battle_visitor.h"
#include <iostream>
#include <algorithm>

BattleManager::BattleManager() {}

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

void BattleManager::addBattleTask(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    battle_queue.push_back({attacker, defender});
}

BattleTask BattleManager::getBattleTask()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    if (battle_queue.empty())
    {
        return {nullptr, nullptr};
    }
    BattleTask task = battle_queue.back();
    battle_queue.pop_back();
    return task;
}

bool BattleManager::hasBattleTasks()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    return !battle_queue.empty();
}

void BattleManager::performBattle(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
{
    if (!attacker->isAlive() || !defender->isAlive())
        return;

    std::string attackerType = attacker->getType();
    std::string defenderType = defender->getType();

    int attack_power = attacker->rollDice();
    int defense_power = defender->rollDice();

    if (attackerType == "Orc")
    {
        if ((defenderType == "Bear" || defenderType == "Squirrel") && attack_power > defense_power)
        {
            defender->setAlive(false);
            std::string result = attacker->getName() + " убил " + defender->getName() +
                                 " (атака: " + std::to_string(attack_power) +
                                 ", защита: " + std::to_string(defense_power) + ")";
            notifyObservers(attacker->getName(), defender->getName(), result);
        }
    }
    else if (attackerType == "Bear")
    {
        if (defenderType == "Squirrel" && attack_power > defense_power)
        {
            defender->setAlive(false);
            std::string result = attacker->getName() + " убил " + defender->getName() +
                                 " (атака: " + std::to_string(attack_power) +
                                 ", защита: " + std::to_string(defense_power) + ")";
            notifyObservers(attacker->getName(), defender->getName(), result);
        }
    }
}

NPCVisitor::NPCVisitor(BattleManager *manager, std::shared_ptr<NPC> npc)
    : battleManager(manager), currentNPC(npc) {}

void BattleVisitor::visit(std::shared_ptr<Orc> orc)
{
    if (currentNPC->getType() != "Orc")
    {
        battleManager->addBattleTask(currentNPC, orc);
    }
}

void BattleVisitor::visit(std::shared_ptr<Bear> bear)
{
    if (currentNPC->getType() != "Bear")
    {
        battleManager->addBattleTask(currentNPC, bear);
    }
}

void BattleVisitor::visit(std::shared_ptr<Squirrel> squirrel)
{
    if (currentNPC->getType() != "Squirrel")
    {
        battleManager->addBattleTask(currentNPC, squirrel);
    }
}