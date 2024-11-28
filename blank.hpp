#pragma once

#include "board.hpp"
#include <string>

class Blank : public Board {
public:
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::optional<std::shared_ptr<Firewall>> getFirewall(int row,
                                                       int col) override;
  char displayChar() const override;
};
