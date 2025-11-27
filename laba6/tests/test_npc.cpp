#include <gtest/gtest.h>
#include "../include/types.h"
#include "../include/npc_factory.h"
#include "../include/battle_visitor.h"

TEST(NPCTest, CreationTest)
{
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    EXPECT_EQ(orc->getName(), "Grom");
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_TRUE(orc->isAlive);
}

TEST(NPCTest, DistanceTest)
{
    auto npc1 = std::make_shared<Orc>("Grom", 0, 0);
    auto npc2 = std::make_shared<Bear>("Misha", 3, 4);

    EXPECT_DOUBLE_EQ(npc1->distanceTo(*npc2), 5.0);
}

TEST(FactoryTest, CreateNPCTest)
{
    auto npc = NPCFactory::createNPC("Orc", "Grom", 10, 20);
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Orc");

    npc = NPCFactory::createNPC("Unknown", "Test", 0, 0);
    EXPECT_EQ(npc, nullptr);
}

TEST(FactoryTest, SerializationTest)
{
    auto original = std::make_shared<Orc>("Grom", 100, 200);
    std::string data = NPCFactory::saveToString(*original);

    auto loaded = NPCFactory::loadFromString(data);
    EXPECT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->getName(), "Grom");
    EXPECT_EQ(loaded->getType(), "Orc");
}

TEST(BattleTest, OrcVsBear)
{
    auto battleManager = std::make_shared<BattleManager>(100.0);

    auto orc = std::make_shared<Orc>("Orc1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 1, 1);

    battleManager->battle(orc, bear);

    EXPECT_FALSE(bear->isAlive);
    EXPECT_TRUE(orc->isAlive);
}

TEST(BattleTest, SquirrelPeaceful)
{
    auto battleManager = std::make_shared<BattleManager>(100.0);

    auto squirrel = std::make_shared<Squirrel>("Sq1", 0, 0);
    auto orc = std::make_shared<Orc>("Orc1", 1, 1);

    battleManager->battle(squirrel, orc);

    // Белка не должна атаковать орка
    EXPECT_TRUE(orc->isAlive);
    EXPECT_TRUE(squirrel->isAlive);
}