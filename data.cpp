#include "data.hpp"

Data::Data(std::shared_ptr<Board> board, Player &player, int row, int col,
           int strength, char linkChar)
    : Link{board, player, row, col, strength, linkChar} {}

char Data::typeChar() const { return 'D'; }

bool Data::battle(std::shared_ptr<Link> o) {
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
