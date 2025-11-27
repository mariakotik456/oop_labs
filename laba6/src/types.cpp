#include "../include/types.h"
#include "../include/battle_visitor.h"

Orc::Orc(const std::string &name, int x, int y) : NPC(name, x, y) {}
void Orc::accept(NPCVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<Orc>(shared_from_this()));
}
std::string Orc::getType() const { return "Orc"; }

Bear::Bear(const std::string &name, int x, int y) : NPC(name, x, y) {}
void Bear::accept(NPCVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<Bear>(shared_from_this()));
}
std::string Bear::getType() const { return "Bear"; }

Squirrel::Squirrel(const std::string &name, int x, int y) : NPC(name, x, y) {}
void Squirrel::accept(NPCVisitor &visitor)
{
    visitor.visit(std::static_pointer_cast<Squirrel>(shared_from_this()));
}
std::string Squirrel::getType() const { return "Squirrel"; }