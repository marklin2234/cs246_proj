#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include <memory>

class Link : public BoardDecorator {
public:
  enum class LinkType { Virus, Data };

protected:
  int row_, col_, strength_;
  LinkType type_;
  bool isDownloaded_;

public:
  explicit Link(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
                int row, int col, int strength, LinkType type);
  std::shared_ptr<Board> getCell(int row, int col) override;
  std::string displayChar() const override;
  int getStrength() const;
  int getRow() const;
  int getCol() const;
  bool getDownloaded() const;
  void setStrength(int strength);
  void setRow(int row);
  void setCol(int col);
  void setDownloaded();
  char getType() const;
};
