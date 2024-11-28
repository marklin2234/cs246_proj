#pragma once

#include "ability.hpp"

class SwapAbility : public Ability {
public:
  SwapAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
