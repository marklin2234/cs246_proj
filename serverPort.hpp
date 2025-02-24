#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include <memory>

class ServerPort : public BoardDecorator {
private:
  int row_, col_;

public:
  ServerPort(std::shared_ptr<Board> board, Player &player, int row, int col);
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::optional<std::shared_ptr<Firewall>> getFirewall(int row,
                                                       int col) override;
  char displayChar() const override;
};
