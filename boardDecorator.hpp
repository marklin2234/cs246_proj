#pragma once

#include "board.hpp"
#include "player.hpp"
#include <memory>

class BoardDecorator : public Board {
protected:
  std::shared_ptr<Board> board_;
  std::shared_ptr<Player> player_;

public:
  BoardDecorator(std::shared_ptr<Board> board, std::shared_ptr<Player> player);
  virtual ~BoardDecorator();
  virtual std::shared_ptr<Board> getCell(int row, int col) override = 0;
  virtual std::string displayChar() const override = 0;
  std::shared_ptr<Player> getPlayer() const;
};
