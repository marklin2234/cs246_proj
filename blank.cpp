#include "blank.hpp"

std::shared_ptr<Board> Blank::getCell(int row, int col) {
  return shared_from_this();
}

std::string Blank::displayChar() const { return "."; }
