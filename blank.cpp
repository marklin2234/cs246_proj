#include "blank.hpp"

std::shared_ptr<Board> Blank::getCell(int row, int col) {
  return shared_from_this();
}

std::optional<std::shared_ptr<Firewall>> Blank::getFirewall(int row, int col) {
  return std::nullopt;
}

char Blank::displayChar() const { return '.'; }
