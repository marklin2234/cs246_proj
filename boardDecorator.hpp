#pragma once

#include "board.hpp"
#include "player.hpp"
#include <memory>

class BoardDecorator : public Board {
protected:
  std::shared_ptr<Board> board_;
  Player &player_;

public:
  BoardDecorator(std::shared_ptr<Board> board, Player &player);
  virtual ~BoardDecorator();
  virtual std::shared_ptr<Board> getCell(int row, int col) override = 0;
  virtual char displayChar() const override = 0;
  std::optional<std::shared_ptr<Firewall>> getFirewall(int row,
                                                       int col) override;
  Player &getPlayer() const;
};
