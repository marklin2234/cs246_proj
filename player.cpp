#include "player.hpp"
#include "link.hpp"

Player::Player(PlayerId id) : id_{id} {
  if (id == PlayerId::P1) {
    linkChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  } else {
    linkChars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  }
}

void Player::addDownload(std::shared_ptr<Link> link) {
  link->setDownloaded();
  downloaded.push_back(link);
}

std::vector<std::shared_ptr<Link>> Player::getDownloaded() const {
  return downloaded;
}

Player::PlayerId Player::getPlayerId() const { return id_; }

std::vector<char> Player::getLinkChars() const { return linkChars; }
