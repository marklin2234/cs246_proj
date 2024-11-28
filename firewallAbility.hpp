#pragma once

#include "ability.hpp"

class FirewallAbility : public Ability {
public:
  FirewallAbility(PlayerId player);
  char displayChar() const override;
  void use(const std::shared_ptr<AbilityParams> params) override;
};
