#include "firewallAbility.hpp"
#include "abilityParams.hpp"
#include "firewall.hpp"
#include "player.hpp"

FirewallAbility::FirewallAbility(PlayerId player) : Ability{player} {}

char FirewallAbility::displayChar() const { return 'F'; }

void FirewallAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<FirewallAbilityParams>(params);
  auto row = p->row_;
  auto col = p->col_;
  auto &board = p->board_;
  auto &player = p->player_;

  if (board->getCell(row, col)->displayChar() != '.') {
    return; // TODO: Throw error (non-empty cell)
  }

  board = std::make_shared<Firewall>(board, player, row, col);
}
