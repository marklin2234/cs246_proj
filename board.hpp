#pragma once

#include <memory>
#include <optional>

class Firewall;

class Board : public std::enable_shared_from_this<Board> {
public:
  virtual ~Board();
  virtual std::shared_ptr<Board> getCell(int row, int col) = 0;
  virtual char displayChar() const = 0;
  virtual std::optional<std::shared_ptr<Firewall>> getFirewall(int row,
                                                               int col) = 0;
};
