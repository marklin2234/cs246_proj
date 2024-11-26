#include "data.hpp"
#include <string>

Data::Data(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
           int row, int col, int strength)
    : Link{board, player, row, col, strength} {}

std::string Data::displayChar() const { return "D"; }

bool Data::battle(std::shared_ptr<Link> o) {
  if (getPlayer()->getPlayerId() == o->getPlayer()->getPlayerId()) {
    return false; // Maybe throw error in future
  }
  if (getStrength() >= o->getStrength()) {
    auto p1 = getPlayer();
    p1->addDownload(o);
    o->setDownloaded();
  } else {
    auto p2 = o->getPlayer();
    p2->addDownload(std::shared_ptr<Data>(this));
    setDownloaded();
  }
  return true;
}
