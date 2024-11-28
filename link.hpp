#pragma once

#include "board.hpp"
#include "boardDecorator.hpp"
#include "serverPort.hpp"
#include <memory>

enum class LinkType {
  Virus,
  Data,
};

class Link : public BoardDecorator {
private:
  int row_, col_, strength_;
  LinkType type_;
  char linkChar_;
  bool isDownloaded_;
  bool isBoosted_;

  std::pair<int, int> directionToVector(char dir) const;
  bool battle(std::shared_ptr<Link> o);
  bool serverDownload(std::shared_ptr<ServerPort> server);

public:
  explicit Link(std::shared_ptr<Board> board, Player &player, int row, int col,
                int strength, char linkType, char linkChar);
  std::shared_ptr<Board> getCell(int row, int col) override;
  char displayChar() const override;
  char typeChar() const;

  int getStrength() const;
  int getRow() const;
  int getCol() const;
  bool getDownloaded() const;
  void setStrength(int strength);
  void setRow(int row);
  void setCol(int col);
  void setDownloaded();
  void setIsBoosted();
  LinkType getLinkType() const;
  void setLinkType(LinkType linkType);

  bool moveLink(char dir, std::shared_ptr<Board> board, int nrows, int ncols);
};
