#include "ability.hpp"

Ability::Ability(Player &player) : player_{player}, used_{false} {}

Player &Ability::getPlayer() const { return player_; }

bool Ability::isUsed() const { return used_; }

void Ability::setUsed() { used_ = true; }
