#pragma once

#include "player.hpp"

class PolarizeAbility : public Ability {
public:
  PolarizeAbility(Player &player);
  void use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
