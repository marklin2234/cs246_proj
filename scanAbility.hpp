#pragma once

#include "ability.hpp"

class ScanAbility : public Ability {
public:
  ScanAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
