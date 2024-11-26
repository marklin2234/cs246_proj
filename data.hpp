#pragma once

#include "link.hpp"

class Data : public Link {
protected:
  bool battle(std::shared_ptr<Link> o) override;

public:
  explicit Data(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
                int row, int col, int strength);

  std::string displayChar() const override;
};
