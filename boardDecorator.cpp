#include "boardDecorator.hpp"

BoardDecorator::BoardDecorator(std::shared_ptr<Board> board,
                               std::shared_ptr<Player> player)
    : board_{board}, player_{player} {}

BoardDecorator::~BoardDecorator() {}

std::shared_ptr<Board> BoardDecorator::getCell(int row, int col) {
  return board_->getCell(row, col);
}

std::shared_ptr<Player> BoardDecorator::getPlayer() const { return player_; }
