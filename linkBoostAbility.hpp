#pragma once

#include "ability.hpp"

class LinkBoostAbility : public Ability {
public:
  LinkBoostAbility(Player &player);
  char displayChar() const override;
  void use(const std::shared_ptr<AbilityParams> params) override;
};
