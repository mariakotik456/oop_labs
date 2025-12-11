#include <gtest/gtest.h>
#include "../include/types.h"
#include "../include/npc_factory.h"
#include "../include/battle_visitor.h"

TEST(NPCTest, CreationTest)
{
    auto orc = std::make_shared<Orc>("Grom", 10, 10);
    EXPECT_EQ(orc->getName(), "Grom");
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_TRUE(orc->isAlive());
    EXPECT_EQ(orc->getMoveDistance(), 20);
    EXPECT_EQ(orc->getKillDistance(), 10);
}

TEST(NPCTest, DistanceTest)
{
    auto npc1 = std::make_shared<Orc>("Grom", 0, 0);
    auto npc2 = std::make_shared<Bear>("Misha", 3, 4);

    EXPECT_DOUBLE_EQ(npc1->distanceTo(*npc2), 5.0);
}

TEST(NPCTest, CanKillTest)
{
    auto orc = std::make_shared<Orc>("Grom", 0, 0);
    auto bear = std::make_shared<Bear>("Misha", 8, 0);

    EXPECT_TRUE(orc->canKill(*bear));
}

TEST(NPCTest, CannotKillTest)
{
    auto orc = std::make_shared<Orc>("Grom", 0, 0);
    auto bear = std::make_shared<Bear>("Misha", 15, 0);

    EXPECT_FALSE(orc->canKill(*bear));
}

TEST(NPCTest, MoveTest)
{
    auto squirrel = std::make_shared<Squirrel>("Sq", 50, 50);
    int initial_x = squirrel->getX();
    int initial_y = squirrel->getY();

    squirrel->move(100, 100);

    EXPECT_GE(squirrel->getX(), 0);
    EXPECT_LE(squirrel->getX(), 99);
    EXPECT_GE(squirrel->getY(), 0);
    EXPECT_LE(squirrel->getY(), 99);
}

TEST(NPCTest, RollDiceTest)
{
    auto orc = std::make_shared<Orc>("Grom", 0, 0);
    int dice_roll = orc->rollDice();

    EXPECT_GE(dice_roll, 1);
    EXPECT_LE(dice_roll, 6);
}

TEST(FactoryTest, CreateRandomNPCTest)
{
    auto npc = NPCFactory::createRandomNPC("Test", 100, 100);
    EXPECT_NE(npc, nullptr);
    EXPECT_TRUE(npc->getType() == "Orc" || npc->getType() == "Bear" || npc->getType() == "Squirrel");
    EXPECT_GE(npc->getX(), 0);
    EXPECT_LE(npc->getX(), 99);
    EXPECT_GE(npc->getY(), 0);
    EXPECT_LE(npc->getY(), 99);
}

TEST(BattleTest, BattleManagerTest)
{
    auto battleManager = std::make_shared<BattleManager>();
    auto orc = std::make_shared<Orc>("Orc1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 1, 1);

    battleManager->addBattleTask(orc, bear);
    EXPECT_TRUE(battleManager->hasBattleTasks());

    BattleTask task = battleManager->getBattleTask();
    EXPECT_NE(task.attacker, nullptr);
    EXPECT_NE(task.defender, nullptr);
    EXPECT_FALSE(battleManager->hasBattleTasks());
}