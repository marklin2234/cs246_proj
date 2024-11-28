#include "boardDecorator.hpp"

BoardDecorator::BoardDecorator(std::shared_ptr<Board> board, Player &player)
    : board_{board}, player_{player} {}

BoardDecorator::~BoardDecorator() {}

std::shared_ptr<Board> BoardDecorator::getCell(int row, int col) {
  return board_->getCell(row, col);
}

std::optional<std::shared_ptr<Firewall>> BoardDecorator::getFirewall(int row,
                                                                     int col) {
  return board_->getFirewall(row, col);
}

Player &BoardDecorator::getPlayer() const { return player_; }
