#pragma once

#include "ability.hpp"

class FirewallAbility : public Ability {
public:
  FirewallAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
