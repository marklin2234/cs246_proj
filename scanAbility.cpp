
#include "scanAbility.hpp"
#include "ability.hpp"
#include "abilityParams.hpp"
#include <iostream>
#include <memory>

ScanAbility::ScanAbility(Player &player) : Ability{player} {}

bool ScanAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<ScanAbilityParams>(params);
  const auto &[link] = *p;
  auto &player = getPlayer();

  if (link->getPlayer().getPlayerId() == player.getPlayerId()) {
    std::cout << "Error. Scanning own link.\n";
    return false;
  }
  player.addSeen(link->displayChar());
  return true;
}

char ScanAbility::displayChar() const { return 'S'; }
