#pragma once

#include <memory>

class Board : public std::enable_shared_from_this<Board> {
public:
  virtual ~Board();
  virtual std::shared_ptr<Board> getCell(int row, int col) = 0;
  virtual std::string displayChar() const = 0;
};
