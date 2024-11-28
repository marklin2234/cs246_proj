#include "serverPort.hpp"
#include "boardDecorator.hpp"
#include <memory>

ServerPort::ServerPort(std::shared_ptr<Board> board, Player &player, int row,
                       int col)
    : BoardDecorator{board, player}, row_{row}, col_{col} {}

std::shared_ptr<Board> ServerPort::getCell(int row, int col) {
  if (row == row_ && col == col_) {
    return shared_from_this();
  }
  return board_->getCell(row, col);
}

std::optional<std::shared_ptr<Firewall>> ServerPort::getFirewall(int row,
                                                                 int col) {
  return board_->getFirewall(row, col);
}

char ServerPort::displayChar() const { return 'S'; }
