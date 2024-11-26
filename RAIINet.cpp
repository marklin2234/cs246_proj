#include "RAIINet.hpp"
#include "board.hpp"
#include "data.hpp"
#include "serverPort.hpp"
#include "virus.hpp"
#include <fstream>
#include <memory>
#include <utility>

RAIINet::RAIINet(std::shared_ptr<Board> board) : board_{board} {
  players[Player::PlayerId::P1] =
      std::make_shared<Player>(Player::PlayerId::P1);
  players[Player::PlayerId::P2] =
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
    int strength = linkInfo[1] - '0';
    if (linkInfo[0] == 'V') {
      board_ = links[linkChars[i]] = std::make_shared<Virus>(
          board_, player, linkPos[i].first, linkPos[i].second, strength);
    } else {
      board_ = links[linkChars[i]] = std::make_shared<Data>(
          board_, player, linkPos[i].first, linkPos[i].second, strength);
    }
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
    out << c->displayChar() << c->getStrength();
    i++;
  }
  out << "\n";
  out << "Abilities: "; // TODO: Add abilities
  out << "\n";
  i = 0;
  // TODO: Hide P2/P1 depending on perspective
  for (const auto c : player->getLinkChars()) {
    out << c << ": " << links.at(c)->displayChar()
        << links.at(c)->getStrength();
    out << ((i == 3) ? "\n" : " ");
    i++;
  }
  out << "\n";
}

void RAIINet::moveLink(char linkChar, char dir) {
  links[linkChar]->moveLink(dir, board_, nrows, ncols);
}
