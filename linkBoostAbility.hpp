#pragma once

#include "ability.hpp"

class LinkBoostAbility : public Ability {
public:
  LinkBoostAbility(Player &player);
  void use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
