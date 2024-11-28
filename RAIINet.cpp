#include "RAIINet.hpp"
#include "abilityParams.hpp"
#include "board.hpp"
#include "downloadAbility.hpp"
#include "firewallAbility.hpp"
#include "linkBoostAbility.hpp"
#include "polarizeAbility.hpp"
#include "scanAbility.hpp"
#include "serverPort.hpp"
#include <fstream>
#include <memory>
#include <utility>

RAIINet::RAIINet(std::shared_ptr<Board> board) : board_{board} {
  players[PlayerId::P1] = Player(PlayerId::P1);
  players[PlayerId::P2] = Player(PlayerId::P2);
}

void RAIINet::displayBoard() const {
  int i = 0, j;
  printPlayerInfo(PlayerId::P1);
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
  printPlayerInfo(PlayerId::P2);
}

void RAIINet::endGame() {}

void RAIINet::setup(int argc, char **argv) {
  std::string command;
  std::string abilityOrder1 = "LFDSP", abilityOrder2 = "LFDSP";
  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "-link1") {
      PlayerId player = PlayerId::P1;
      if (i + 1 < argc) {
        RAIINet::linkSetup(player, argv[i + 1]);
      }
      board_ = std::make_shared<ServerPort>(board_, players[player], 0, 3);
      board_ = std::make_shared<ServerPort>(board_, players[player], 0, 4);
    } else if (std::string(argv[i]) == "-link2") {
      PlayerId player = PlayerId::P2;
      if (i + 1 < argc) {
        RAIINet::linkSetup(player, argv[i + 1]);
      }
      board_ = std::make_shared<ServerPort>(board_, players[player], 7, 3);
      board_ = std::make_shared<ServerPort>(board_, players[player], 7, 4);
    } else if (std::string(argv[i]) == "-ability1") {
      if (i + 1 < argc) {
        abilityOrder1 = argv[i + 1];
      }
    } else if (std::string(argv[i]) == "-ability2") {
      if (i + 1 < argc) {
        abilityOrder2 = argv[i + 1];
      }
    }
  }
  RAIINet::abilitySetup(PlayerId::P1, abilityOrder1);
  RAIINet::abilitySetup(PlayerId::P2, abilityOrder2);
}

void RAIINet::linkSetup(PlayerId pid, const std::string &linkFile) {
  std::ifstream file(linkFile.c_str());
  using pii = std::pair<int, int>;
  std::vector<pii> linkPos;
  Player &player = players[pid];
  const std::vector<char> &linkChars = player.getLinkChars();
  if (pid == PlayerId::P1) {
    linkPos = {{0, 0}, {0, 1}, {0, 2}, {1, 3}, {1, 4}, {0, 5}, {0, 6}, {0, 7}};
  } else if (pid == PlayerId::P2) {
    linkPos = {{7, 0}, {7, 1}, {7, 2}, {6, 3}, {6, 4}, {7, 5}, {7, 6}, {7, 7}};
  }

  std::string linkInfo;
  int i = 0;
  while (file >> linkInfo) {
    int strength = linkInfo[1] - '0';
    board_ = links[linkChars[i]] = std::make_shared<Link>(
        board_, player, linkPos[i].first, linkPos[i].second, strength,
        linkInfo[0], linkChars[i]);
    i++;
  }
}

void RAIINet::abilitySetup(PlayerId pid, const std::string &order) {
  auto &player = players[pid];

  for (const auto c : order) {
    player.addAbility(c);
  }
}

void RAIINet::printPlayerInfo(PlayerId pid) const {
  const auto &player = players.at(pid);
  const auto &seenLinks = players.at(turn).getSeen();
  out << "Player " << static_cast<int>(pid) + 1 << ":\n";
  out << "Downloaded: " << std::to_string(player.getNumDataDownloaded())
      << "D, " << std::to_string(player.getNumVirusDownloaded()) << "V";
  out << "\n";
  out << "Abilities: " << player.getNumAbilities();
  out << "\n";
  int i = 0;
  // TODO: Hide P2/P1 depending on perspective
  for (const auto c : player.getLinkChars()) {
    out << c << ": ";
    if (player.getPlayerId() == turn ||
        std::find(seenLinks.begin(), seenLinks.end(), c) != seenLinks.end()) {
      out << links.at(c)->typeChar() << links.at(c)->getStrength();
    } else {
      out << "?";
    }
    out << ((i == 3) ? "\n" : " ");
    i++;
  }
  out << "\n";
}

void RAIINet::endTurn() {
  int next = static_cast<int>(turn);
  next = (next + 1) % numPlayers;

  turn = static_cast<PlayerId>(next);
}

void RAIINet::moveLink(char linkChar, char dir) {
  auto &player = players[turn];
  auto &linkChars = player.getLinkChars();

  if (std::find(linkChars.begin(), linkChars.end(), linkChar) ==
          linkChars.end() ||
      links[linkChar]->getDownloaded()) {
    std::cout << "Error. Not your link, or already downloaded.\n";
    return;
  }
  links[linkChar]->moveLink(dir, board_, nrows, ncols);
  endTurn();
}

void RAIINet::useAbility(int N, const std::vector<std::string> &params) {
  auto &player = players[turn];
  auto &abilities = player.getAbilities();
  N--;

  if (abilities[N]->isUsed()) {
    std::cout << "Error. Ability already used.\n";
    return; // TODO: add error (ability already used)
  }

  std::shared_ptr<AbilityParams> abilityParams;

  // TODO: Add bad input handling
  if (dynamic_cast<LinkBoostAbility *>(abilities[N].get())) {
    char linkChar = params[0][0];
    abilityParams = std::make_shared<LinkBoostAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<FirewallAbility *>(abilities[N].get())) {
    int row = stoi(params[0]), col = stoi(params[1]);
    abilityParams = std::make_shared<FirewallAbilityParams>(row, col, board_,
                                                            players[turn]);
  } else if (dynamic_cast<DownloadAbility *>(abilities[N].get())) {
    char linkChar = params[0][0];
    abilityParams = std::make_shared<DownloadAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<PolarizeAbility *>(abilities[N].get())) {
    char linkChar = params[0][0];
    abilityParams = std::make_shared<PolarizeAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<ScanAbility *>(abilities[N].get())) {
    char linkChar = params[0][0];
    abilityParams = std::make_shared<ScanAbilityParams>(links[linkChar]);
  }
  if (abilities[N]->use(abilityParams)) {
    abilities[N]->setUsed();
    player.useAbility();
  }
}

void RAIINet::displayAbilities() const {
  auto &player = players.at(turn);
  auto &abilities = player.getAbilities();

  for (const auto &ability : abilities) {
    out << ability->displayChar() << (ability->isUsed() ? 'U' : 'A') << " ";
  }
  out << "\n";
}
