#pragma once
#include "types.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <mutex>

struct BattleTask
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class BattleManager
{
private:
    std::vector<std::shared_ptr<BattleObserver>> observers;
    std::vector<BattleTask> battle_queue;
    std::mutex queue_mutex;

public:
    BattleManager();

    void addObserver(std::shared_ptr<BattleObserver> observer);
    void removeObserver(std::shared_ptr<BattleObserver> observer);

    void addBattleTask(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);
    BattleTask getBattleTask();
    bool hasBattleTasks();

    void performBattle(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);

private:
    void notifyObservers(const std::string &killer,
                         const std::string &victim,
                         const std::string &result);
};

class NPCVisitor
{
protected:
    BattleManager *battleManager;
    std::shared_ptr<NPC> currentNPC;

public:
    NPCVisitor(BattleManager *manager, std::shared_ptr<NPC> npc);
    virtual ~NPCVisitor() = default;

    virtual void visit(std::shared_ptr<Orc> orc) = 0;
    virtual void visit(std::shared_ptr<Bear> bear) = 0;
    virtual void visit(std::shared_ptr<Squirrel> squirrel) = 0;
};

class BattleVisitor : public NPCVisitor
{
public:
    using NPCVisitor::NPCVisitor;

    void visit(std::shared_ptr<Orc> orc) override;
    void visit(std::shared_ptr<Bear> bear) override;
    void visit(std::shared_ptr<Squirrel> squirrel) override;
};