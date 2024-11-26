#include "RAIINet.hpp"
#include "board.hpp"
#include "link.hpp"
#include "serverPort.hpp"
#include <fstream>
#include <memory>
#include <utility>

RAIINet::RAIINet(std::shared_ptr<Board> board) : board_{board} {
  auto p1 = players[Player::PlayerId::P1] =
      std::make_shared<Player>(Player::PlayerId::P1);
  auto p2 = players[Player::PlayerId::P2] =
      std::make_shared<Player>(Player::PlayerId::P2);
}

void RAIINet::displayBoard() const {
  int i = 0, j;
  printPlayerInfo(Player::PlayerId::P1);
  for (i = 0; i < ncols; i++) {
    out << "=";
  }
  out << "\n";
  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      auto cell = board_->getCell(i, j);
      out << cell->displayChar();
    }
    out << "\n";
  }
  for (i = 0; i < ncols; i++) {
    out << "=";
  }
  out << "\n";
  printPlayerInfo(Player::PlayerId::P2);
}

void RAIINet::endGame() {}

std::pair<int, int> RAIINet::directionToVector(char dir) const {
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

void RAIINet::setup(int argc, char **argv) {
  std::string command;
  std::string abilityOrder1 = "LFDSP", abilityOrder2 = "LFDSP";
  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "-link1") {
      Player::PlayerId player = Player::PlayerId::P1;
      if (i + 1 < argc) {
        RAIINet::linkSetup(player, argv[i + 1]);
      }
      board_ = std::make_shared<ServerPort>(board_, players[player], 0, 3);
      board_ = std::make_shared<ServerPort>(board_, players[player], 0, 4);
    } else if (std::string(argv[i]) == "-link2") {
      Player::PlayerId player = Player::PlayerId::P2;
      if (i + 1 < argc) {
        RAIINet::linkSetup(player, argv[i + 1]);
      }
      board_ = std::make_shared<ServerPort>(board_, players[player], 7, 3);
      board_ = std::make_shared<ServerPort>(board_, players[player], 7, 4);
    } else if (std::string(argv[i]) == "-ability1") {

    } else if (std::string(argv[i]) == "-ability2") {
    }
  }
}

/* Assumes l1 is the link that initiated the battle. */
void RAIINet::linkBattle(std::shared_ptr<Link> l1, std::shared_ptr<Link> l2) {
  if (l1->getPlayer()->getPlayerId() == l2->getPlayer()->getPlayerId()) {
    return; // Maybe throw error in future
  }
  if (l1->getStrength() >= l2->getStrength()) {
    auto p1 = l1->getPlayer();
    p1->addDownload(l2);
    l2->setDownloaded();
  } else {
    auto p2 = l2->getPlayer();
    p2->addDownload(l1);
    l1->setDownloaded();
  }
}

void RAIINet::serverDownload(std::shared_ptr<Link> link,
                             std::shared_ptr<ServerPort> server) {
  if (link->getPlayer()->getPlayerId() != server->getPlayer()->getPlayerId()) {
    link->getPlayer()->addDownload(link);
    link->setDownloaded();
  }
}

void RAIINet::linkSetup(Player::PlayerId pid, const std::string &linkFile) {
  std::ifstream file(linkFile.c_str());
  using pii = std::pair<int, int>;
  std::vector<pii> linkPos;
  std::shared_ptr<Player> player = players[pid];
  std::vector<char> linkChars = player->getLinkChars();
  if (pid == Player::PlayerId::P1) {
    linkPos = {{0, 0}, {0, 1}, {0, 2}, {1, 3}, {1, 4}, {0, 5}, {0, 6}, {0, 7}};
  } else if (pid == Player::PlayerId::P2) {
    linkPos = {{7, 0}, {7, 1}, {7, 2}, {6, 3}, {6, 4}, {7, 5}, {7, 6}, {7, 7}};
  }

  std::string linkInfo;
  int i = 0;
  while (file >> linkInfo) {
    Link::LinkType type =
        linkInfo[0] == 'V' ? Link::LinkType::Virus : Link::LinkType::Data;
    int strength = linkInfo[1] - '0';
    board_ = links[linkChars[i]] = std::make_shared<Link>(
        board_, player, linkPos[i].first, linkPos[i].second, strength, type);
    i++;
  }
}

void RAIINet::printPlayerInfo(Player::PlayerId pid) const {
  auto player = players.at(pid);
  out << "Player " << static_cast<int>(pid) + 1 << ":\n";
  out << "Downloaded: ";
  int i = 0;
  for (const auto &c : player->getDownloaded()) {
    if (i != 0) {
      out << ", ";
    }
    out << c->getType() << c->getStrength();
    i++;
  }
  out << "\n";
  out << "Abilities: "; // TODO: Add abilities
  out << "\n";
  i = 0;
  // TODO: Hide P2/P1 depending on perspective
  for (const auto c : player->getLinkChars()) {
    out << c << ": " << links.at(c)->getType() << links.at(c)->getStrength();
    out << ((i == 3) ? "\n" : " ");
    i++;
  }
  out << "\n";
}

void RAIINet::moveLink(char linkChar, char dir) {
  auto d = directionToVector(dir);
  std::shared_ptr<Link> link = links[linkChar];
  if (link->getDownloaded()) {
    return; // Throw error in future
  }

  int r = link->getRow() + d.first, c = link->getCol() + d.second;

  if (r < 0 && link->getPlayer()->getPlayerId() == Player::PlayerId::P2) {
    players[Player::PlayerId::P1]->addDownload(link);
    link->setDownloaded();
  } else if (r >= nrows &&
             link->getPlayer()->getPlayerId() == Player::PlayerId::P1) {
    players[Player::PlayerId::P2]->addDownload(link);
    link->setDownloaded();
  } else if (r < 0 || r >= nrows || c < 0 || c >= ncols) {
    return; // Throw error in future
  } else if (auto cell = board_->getCell(r, c)) {
    if (auto otherLink = std::dynamic_pointer_cast<Link>(cell)) {
      RAIINet::linkBattle(link, otherLink);
    } else if (auto serverLink = std::dynamic_pointer_cast<ServerPort>(cell)) {
      RAIINet::serverDownload(link, serverLink);
    }
  }
  link->setRow(r);
  link->setCol(c);
}
