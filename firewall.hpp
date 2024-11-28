#pragma once

#include "boardDecorator.hpp"

class Firewall : public BoardDecorator {
private:
  int row_, col_;

public:
  Firewall(std::shared_ptr<Board> board, Player &player, int row, int col);
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::optional<std::shared_ptr<Firewall>> getFirewall(int row,
                                                       int col) override;
  char displayChar() const override;
};
