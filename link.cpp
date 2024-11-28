#include "link.hpp"
#include "boardDecorator.hpp"
#include "firewall.hpp"
#include <iostream>

std::pair<int, int> Link::directionToVector(char dir) const {
  switch (dir) {
  case 'u':
    return {-1, 0};
  case 'd':
    return {1, 0};
  case 'l':
    return {0, -1};
  case 'r':
    return {0, 1};
  }
  return {0, 0};
}

bool Link::battle(std::shared_ptr<Link> o) {
  if (getPlayer().getPlayerId() == o->getPlayer().getPlayerId()) {
    return false; // Maybe throw error in future
  }
  if (getStrength() >= o->getStrength()) {
    auto &p1 = getPlayer();
    p1.addDownload(o);
    o->setDownloaded();
  } else {
    auto &p2 = o->getPlayer();
    p2.addDownload(std::dynamic_pointer_cast<Link>(shared_from_this()));
    setDownloaded();
  }
  return true;
}

bool Link::serverDownload(std::shared_ptr<ServerPort> server) {
  if (getPlayer().getPlayerId() != server->getPlayer().getPlayerId()) {
    server->getPlayer().addDownload(
        std::dynamic_pointer_cast<Link>(shared_from_this()));
    setDownloaded();
    return true;
  }
  return false;
}

Link::Link(std::shared_ptr<Board> board, Player &player, int row, int col,
           int strength, char linkType, char linkChar)
    : BoardDecorator(board, player), row_{row}, col_{col}, strength_{strength},
      linkChar_{linkChar}, isDownloaded_{false}, isBoosted_{false} {
  if (linkType == 'V') {
    type_ = LinkType::Virus;
  } else if (linkType == 'D') {
    type_ = LinkType::Data;
  }
}

std::shared_ptr<Board> Link::getCell(int row, int col) {
  if (!isDownloaded_ && row == row_ && col == col_) {
    return shared_from_this();
  }

  return board_->getCell(row, col);
}

char Link::displayChar() const { return linkChar_; }

char Link::typeChar() const {
  if (type_ == LinkType::Virus) {
    return 'V';
  } else if (type_ == LinkType::Data) {
    return 'D';
  }
  return '?';
}

int Link::getStrength() const { return strength_; }
int Link::getRow() const { return row_; }
int Link::getCol() const { return col_; }
bool Link::getDownloaded() const { return isDownloaded_; }
void Link::setStrength(int strength) { strength_ = strength; }
void Link::setRow(int row) { row_ = row; }
void Link::setCol(int col) { col_ = col; }
void Link::setDownloaded() { isDownloaded_ = true; }
void Link::setIsBoosted() { isBoosted_ = true; }
LinkType Link::getLinkType() const { return type_; }
void Link::setLinkType(LinkType linkType) { type_ = linkType; }

void Link::moveLink(char dir, std::shared_ptr<Board> board, int nrows,
                    int ncols) {
  auto d = directionToVector(dir);
  if (getDownloaded()) {
    return; // TODO: Throw error (Already downloaded)
  }
  if (isBoosted_) {
    d.first *= 2;
    d.second *= 2;
  }

  int r = getRow() + d.first, c = getCol() + d.second;

  if (r < 0 && getPlayer().getPlayerId() == PlayerId::P2) {
    getPlayer().addDownload(std::static_pointer_cast<Link>(shared_from_this()));
  } else if (r >= nrows && getPlayer().getPlayerId() == PlayerId::P1) {
    getPlayer().addDownload(std::static_pointer_cast<Link>(shared_from_this()));
  } else if (r < 0 || r >= nrows || c < 0 || c >= ncols) {
    std::cout << "Error. Trying to move out of bounds.\n";
    return; // TODO: Throw error (OOB exception)
  } else if (auto firewall = board->getFirewall(r, c)) {
    auto &player = firewall->get()->getPlayer();
    if (player.getPlayerId() != getPlayer().getPlayerId()) {
      player.addSeen(displayChar());

      if (type_ == LinkType::Virus) {
        getPlayer().addDownload(
            std::static_pointer_cast<Link>(shared_from_this()));
      }
    }
  } else if (auto cell = board->getCell(r, c)) {
    if (auto otherLink = std::dynamic_pointer_cast<Link>(cell)) {
      if (!battle(otherLink)) {
        std::cout << "Error: Trying to move onto own link.\n";
        return; // TODO: Throw error (trying to move onto own link)
      }
    } else if (auto serverLink = std::dynamic_pointer_cast<ServerPort>(cell)) {
      if (!serverDownload(serverLink)) {
        std::cout << "Error: Trying to move onto own server.\n";
        return; // TODO: Throw error (trying to move onto own server)
      }
    }
  }
  setRow(r);
  setCol(c);
}
