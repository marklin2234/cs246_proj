#include "player.hpp"
#include "downloadAbility.hpp"
#include "firewallAbility.hpp"
#include "link.hpp"
#include "linkBoostAbility.hpp"
#include "linkCleanseAbility.hpp"
#include "linkHideAbility.hpp"
#include "polarizeAbility.hpp"
#include "scanAbility.hpp"
#include "swapAbility.hpp"

Player::Player(PlayerId id) : id_{id} {
  if (id == PlayerId::P1) {
    linkChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  } else {
    linkChars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  }
}

Player::Player(Player &&player)
    : id_{player.id_}, linkChars{std::move(player.linkChars)},
      abilities{std::move(player.abilities)} {}

Player &Player::operator=(Player &&player) {
  if (&player == this) {
    return *this;
  }
  id_ = player.id_;
  linkChars = std::move(player.linkChars);
  abilities = std::move(player.abilities);

  return *this;
}

void Player::addDownload(std::shared_ptr<Link> link) {
  link->setDownloaded();
  if (link->typeChar() == 'V') {
    numVirusDownloaded++;
  } else if (link->typeChar() == 'D') {
    numDataDownloaded++;
  }
}

int Player::getNumDataDownloaded() const { return numDataDownloaded; }

int Player::getNumVirusDownloaded() const { return numVirusDownloaded; }

void Player::addAbility(char c) {
  switch (c) {
  case 'L':
    abilities.emplace_back(std::make_unique<LinkBoostAbility>(*this));
    break;
  case 'F':
    abilities.emplace_back(std::make_unique<FirewallAbility>(*this));
    break;
  case 'D':
    abilities.emplace_back(std::make_unique<DownloadAbility>(*this));
    break;
  case 'P':
    abilities.emplace_back(std::make_unique<PolarizeAbility>(*this));
    break;
  case 'S':
    abilities.emplace_back(std::make_unique<ScanAbility>(*this));
    break;
  case 'C':
    abilities.emplace_back(std::make_unique<SwapAbility>(*this));
    break;
  case 'H':
    abilities.emplace_back(std::make_unique<LinkHideAbility>(*this));
    break;
  case 'E':
    abilities.emplace_back(std::make_unique<LinkCleanseAbility>(*this));
    break;
  }
}

PlayerId Player::getPlayerId() const { return id_; }

const std::vector<char> &Player::getLinkChars() const { return linkChars; }

const std::vector<std::unique_ptr<Ability>> &Player::getAbilities() const {
  return abilities;
}

int Player::getNumAbilities() const { return numUnusedAbilities; }

void Player::useAbility() { numUnusedAbilities--; }

void Player::addSeen(char linkChar) { seen.insert(linkChar); }

const std::unordered_set<char> &Player::getSeen() const { return seen; }
