#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include "serverPort.hpp"
#include <memory>

class Link : public BoardDecorator {
protected:
  int row_, col_, strength_;
  bool isDownloaded_;

  std::pair<int, int> directionToVector(char dir) const;
  virtual bool battle(std::shared_ptr<Link> o) = 0;
  bool serverDownload(std::shared_ptr<ServerPort> server);

public:
  explicit Link(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
                int row, int col, int strength);
  std::shared_ptr<Board> getCell(int row, int col) override;
  virtual std::string displayChar() const override = 0;
  virtual ~Link();

  /* Assume this link is initiating the battle. */
  int getStrength() const;
  int getRow() const;
  int getCol() const;
  bool getDownloaded() const;
  void setStrength(int strength);
  void setRow(int row);
  void setCol(int col);
  void setDownloaded();

  void moveLink(char dir, std::shared_ptr<Board> board, int nrows, int ncols);
};
