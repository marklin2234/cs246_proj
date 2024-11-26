#pragma once

#include "board.hpp"
#include <string>

class Blank : public Board {
public:
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::string displayChar() const override;
};
