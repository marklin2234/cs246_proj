#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include <memory>

class ServerPort : public BoardDecorator {
private:
  int row_, col_;

public:
  ServerPort(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
             int row, int col);
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::string displayChar() const override;
};
