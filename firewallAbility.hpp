#pragma once

#include "ability.hpp"

class FirewallAbility : public Ability {
public:
  FirewallAbility(Player &player);
  char displayChar() const override;
  void use(const std::shared_ptr<AbilityParams> params) override;
};
