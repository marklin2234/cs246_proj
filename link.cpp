#include "link.hpp"
#include "boardDecorator.hpp"

Link::Link(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
           int row, int col, int strength, Link::LinkType type)
    : BoardDecorator(board, player), row_{row}, col_{col}, strength_{strength},
      type_{type}, isDownloaded_{false} {}

std::shared_ptr<Board> Link::getCell(int row, int col) {
  if (!isDownloaded_ && row == row_ && col == col_) {
    return shared_from_this();
  }

  return board_->getCell(row, col);
}
std::string Link::displayChar() const {
  if (type_ == Link::LinkType::Virus) {
    return "V";
  } else {
    return "D";
  }
}

int Link::getStrength() const { return strength_; }
int Link::getRow() const { return row_; }
int Link::getCol() const { return col_; }
bool Link::getDownloaded() const { return isDownloaded_; }
void Link::setStrength(int strength) { strength_ = strength; }
void Link::setRow(int row) { row_ = row; }
void Link::setCol(int col) { col_ = col; }
void Link::setDownloaded() { isDownloaded_ = true; }
char Link::getType() const {
  return type_ == Link::LinkType::Virus ? 'V' : 'D';
}
