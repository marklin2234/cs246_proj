#pragma once

#include "ability.hpp"

class DownloadAbility : public Ability {
public:
  DownloadAbility(Player &player);
  bool use(const std::shared_ptr<AbilityParams> params) override;
  char displayChar() const override;
};
