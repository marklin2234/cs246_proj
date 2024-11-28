#include "linkHideAbility.hpp"
#include "abilityParams.hpp"
#include <iostream>

LinkHideAbility::LinkHideAbility(Player &player) : Ability(player) {}

char LinkHideAbility::displayChar() const { return 'H'; }

bool LinkHideAbility::use(const std::shared_ptr<AbilityParams> params) {
  const auto param = static_pointer_cast<LinkHideAbilityParams>(params);
  auto link = param->link_;
  if (link->getPlayer().getPlayerId() != getPlayer().getPlayerId()) {
    std::cout << "Error. Must link hide own link.\n";
    return false;
  }
  link->setIsHidden();
  return true;
}
