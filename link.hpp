#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include "serverPort.hpp"
#include <memory>

class Link : public BoardDecorator {
protected:
  int row_, col_, strength_;
  char linkChar_;
  bool isDownloaded_;
  bool isBoosted_;

  std::pair<int, int> directionToVector(char dir) const;
  virtual bool battle(std::shared_ptr<Link> o) = 0;
  bool serverDownload(std::shared_ptr<ServerPort> server);

public:
  explicit Link(std::shared_ptr<Board> board, Player &player, int row, int col,
                int strength, char linkChar);
  virtual ~Link();
  std::shared_ptr<Board> getCell(int row, int col) override;
  char displayChar() const override;
  virtual char typeChar() const = 0;

  int getStrength() const;
  int getRow() const;
  int getCol() const;
  bool getDownloaded() const;
  void setStrength(int strength);
  void setRow(int row);
  void setCol(int col);
  void setDownloaded();
  void setIsBoosted();

  void moveLink(char dir, std::shared_ptr<Board> board, int nrows, int ncols);
};
