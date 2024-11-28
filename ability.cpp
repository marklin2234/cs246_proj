#include "ability.hpp"

Ability::Ability(PlayerId player) : player_{player}, used_{false} {}

PlayerId Ability::getPlayerId() const { return player_; }

bool Ability::isUsed() const { return used_; }

void Ability::setUsed() { used_ = true; }
