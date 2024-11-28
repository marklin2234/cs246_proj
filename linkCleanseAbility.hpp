#pragma once

#include "ability.hpp"

class LinkCleanseAbility : public Ability {
public:
  LinkCleanseAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
