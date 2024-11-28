#include "swapAbility.hpp"
#include "abilityParams.hpp"
#include <iostream>

SwapAbility::SwapAbility(Player &player) : Ability{player} {}
bool SwapAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<SwapAbilityParams>(params);
  auto &[link1, link2] = *p;

  const auto &p1 = link1->getPlayer().getPlayerId();
  const auto &p2 = link2->getPlayer().getPlayerId();

  if (p1 != player_.getPlayerId() || p2 != player_.getPlayerId()) {
    std::cout << "Error. You do not own at least one of the selected links.\n";
    return false;
  }

  int tmp = link1->getRow();
  link1->setRow(link2->getRow());
  link2->setRow(tmp);

  tmp = link1->getCol();
  link1->setCol(link2->getCol());
  link2->setCol(tmp);
  return true;
}

char SwapAbility::displayChar() const { return 'C'; }
