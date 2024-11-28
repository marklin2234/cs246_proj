#include "firewallAbility.hpp"
#include "abilityParams.hpp"
#include "firewall.hpp"
#include "player.hpp"
#include <iostream>

FirewallAbility::FirewallAbility(Player &player) : Ability{player} {}

char FirewallAbility::displayChar() const { return 'F'; }

bool FirewallAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<FirewallAbilityParams>(params);
  const auto &[row, col, board, player] = *p;

  if (board->getCell(row, col)->displayChar() != '.') {
    std::cout << "Error. Cannot place firewall on non-empty cell.\n";
    return false;
  }

  board = std::make_shared<Firewall>(board, player, row, col);
  return true;
}
