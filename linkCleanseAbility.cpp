#include "linkCleanseAbility.hpp"
#include "abilityParams.hpp"

LinkCleanseAbility::LinkCleanseAbility(Player &player) : Ability(player) {}

char LinkCleanseAbility::displayChar() const { return 'E'; }

bool LinkCleanseAbility::use(const std::shared_ptr<AbilityParams> params) {
  const auto param = static_pointer_cast<LinkCleanseAbilityParams>(params);
  auto link = param->link_;
  link->setIsHidden(false);
  link->setIsBoosted(false);
  return true;
}
