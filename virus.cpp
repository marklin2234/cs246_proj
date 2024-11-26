#include "virus.hpp"
#include <string>

Virus::Virus(std::shared_ptr<Board> board, std::shared_ptr<Player> player,
             int row, int col, int strength)
    : Link{board, player, row, col, strength} {}

std::string Virus::displayChar() const { return "V"; }

bool Virus::battle(std::shared_ptr<Link> o) {
  if (getPlayer()->getPlayerId() == o->getPlayer()->getPlayerId()) {
    return false; // Maybe throw error in future
  }
  if (getStrength() >= o->getStrength()) {
    auto p1 = getPlayer();
    p1->addDownload(o);
    o->setDownloaded();
  } else {
    auto p2 = o->getPlayer();
    p2->addDownload(std::shared_ptr<Virus>(this));
    setDownloaded();
  }
  return true;
}
