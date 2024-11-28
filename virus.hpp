#pragma once

#include "link.hpp"

class Virus : public Link {
protected:
  bool battle(std::shared_ptr<Link> o) override;

public:
  explicit Virus(std::shared_ptr<Board> board, Player &player, int row, int col,
                 int strength, char linkChar);
  char typeChar() const override;
};
