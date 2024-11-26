#include "link.hpp"
#include "boardDecorator.hpp"

std::pair<int, int> Link::directionToVector(char dir) const {
  switch (dir) {
  case 'u':
    return {-1, 0};
  case 'd':
    return {1, 0};
  case 'l':
    return {0, -1};
  default:
    return {0, 1};
  }
}

bool Link::serverDownload(std::shared_ptr<ServerPort> server) {
  if (getPlayer()->getPlayerId() != server->getPlayer()->getPlayerId()) {
    server->getPlayer()->addDownload(std::shared_ptr<Link>(this));
    setDownloaded();
    return true;
  }
  return false;
}

Link::Link(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
           int row, int col, int strength)
    : BoardDecorator(board, player), row_{row}, col_{col}, strength_{strength},
      isDownloaded_{false} {}

Link::~Link() {}

std::shared_ptr<Board> Link::getCell(int row, int col) {
  if (!isDownloaded_ && row == row_ && col == col_) {
    return shared_from_this();
  }

  return board_->getCell(row, col);
}

int Link::getStrength() const { return strength_; }
int Link::getRow() const { return row_; }
int Link::getCol() const { return col_; }
bool Link::getDownloaded() const { return isDownloaded_; }
void Link::setStrength(int strength) { strength_ = strength; }
void Link::setRow(int row) { row_ = row; }
void Link::setCol(int col) { col_ = col; }
void Link::setDownloaded() { isDownloaded_ = true; }

void Link::moveLink(char dir, std::shared_ptr<Board> board, int nrows,
                    int ncols) {
  auto d = directionToVector(dir);
  if (getDownloaded()) {
    return; // TODO: Throw error (Already downloaded)
  }

  int r = getRow() + d.first, c = getCol() + d.second;

  if (r < 0 && getPlayer()->getPlayerId() == Player::PlayerId::P2) {
    getPlayer()->addDownload(std::shared_ptr<Link>(this));
    setDownloaded();
  } else if (r >= nrows && getPlayer()->getPlayerId() == Player::PlayerId::P1) {
    getPlayer()->addDownload(std::shared_ptr<Link>(this));
    setDownloaded();
  } else if (r < 0 || r >= nrows || c < 0 || c >= ncols) {
    return; // TODO: Throw error (OOB exception)
    //
  } else if (auto cell = board->getCell(r, c)) {
    if (auto otherLink = std::dynamic_pointer_cast<Link>(cell)) {
      if (!battle(otherLink))
        return; // TODO: Throw error (trying to move onto own link)
    } else if (auto serverLink = std::dynamic_pointer_cast<ServerPort>(cell)) {
      if (!serverDownload(serverLink))
        return; // TODO: Throw error (trying to move onto own server)
    }
  }
  setRow(r);
  setCol(c);
}
