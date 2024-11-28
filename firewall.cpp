#include "firewall.hpp"
#include "boardDecorator.hpp"
#include <memory>

Firewall::Firewall(std::shared_ptr<Board> board, Player &player, int row,
                   int col)
    : BoardDecorator{board, player}, row_{row}, col_{col} {}

std::shared_ptr<Board> Firewall::getCell(int row, int col) {
  auto under = board_->getCell(row, col);
  if (under->displayChar() != '.') {
    return under;
  } else if (row == row_ && col == col_) {
    return shared_from_this();
  }
  return under;
}

std::optional<std::shared_ptr<Firewall>> Firewall::getFirewall(int row,
                                                               int col) {
  if (row == row_ && col == col_) {
    return std::static_pointer_cast<Firewall>(shared_from_this());
  }
  return board_->getFirewall(row, col);
}

char Firewall::displayChar() const {
  if (getPlayer().getPlayerId() == PlayerId::P1) {
    return 'M';
  } else {
    return 'W';
  }
}
