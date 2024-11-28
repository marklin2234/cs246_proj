#pragma once

#include "link.hpp"

class Data : public Link {
protected:
  bool battle(std::shared_ptr<Link> o) override;

public:
  explicit Data(std::shared_ptr<Board> board, Player &player, int row, int col,
                int strength, char linkChar);
  char typeChar() const override;
};
