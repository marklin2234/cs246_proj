#include "linkBoostAbility.hpp"
#include "abilityParams.hpp"
#include <iostream>

LinkBoostAbility::LinkBoostAbility(Player &player) : Ability(player) {}

char LinkBoostAbility::displayChar() const { return 'L'; }

bool LinkBoostAbility::use(const std::shared_ptr<AbilityParams> params) {
  const auto param = static_pointer_cast<LinkBoostAbilityParams>(params);
  auto link = param->link_;
  if (link->getPlayer().getPlayerId() != getPlayer().getPlayerId()) {
    std::cout << "Error. Must link boost own link.\n";
    return false;
  }
  link->setIsBoosted(true);
  return true;
}
