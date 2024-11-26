#pragma once

#include "link.hpp"

class Virus : public Link {
protected:
  bool battle(std::shared_ptr<Link> o) override;

public:
  explicit Virus(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
                 int row, int col, int strength);

  std::string displayChar() const override;
};
