#pragma once

#include "ability.hpp"

class LinkHideAbility : public Ability {
public:
  LinkHideAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
