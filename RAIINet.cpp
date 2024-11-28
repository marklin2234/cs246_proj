#include "RAIINet.hpp"
#include "abilityParams.hpp"
#include "board.hpp"
#include "downloadAbility.hpp"
#include "firewallAbility.hpp"
#include "linkBoostAbility.hpp"
#include "linkCleanseAbility.hpp"
#include "linkHideAbility.hpp"
#include "polarizeAbility.hpp"
#include "scanAbility.hpp"
#include "serverPort.hpp"
#include "swapAbility.hpp"
#include <fstream>
#include <memory>
#include <random>
#include <utility>

RAIINet::RAIINet(std::shared_ptr<Board> board) : board_{board} {
  players[PlayerId::P1] = Player(PlayerId::P1);
  players[PlayerId::P2] = Player(PlayerId::P2);
}

void RAIINet::displayBoard() const { notifyObservers(); }

char RAIINet::getState(int row, int col) const {
  auto cell = board_->getCell(row, col);
  return cell->displayChar();
}

void RAIINet::endGame() { isGameOver = true; }

bool RAIINet::getIsGameOver() const { return isGameOver; }

void RAIINet::setup(int argc, char **argv) {
  std::string command;
  std::vector<std::string> link1Order = {"V1", "V2", "V3", "V4",
                                         "D1", "D2", "D3", "D4"};
  std::vector<std::string> link2Order = {"V1", "V2", "V3", "V4",
                                         "D1", "D2", "D3", "D4"};
  auto rng = std::default_random_engine{};
  std::ranges::shuffle(link1Order, rng);
  std::ranges::shuffle(link2Order, rng);
  std::string abilityOrder1 = "LFDSP", abilityOrder2 = "LFDSP";
  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "-link1") {
      if (i + 1 < argc) {
        RAIINet::linkOrderSetup(link1Order, argv[i + 1]);
      }
    } else if (std::string(argv[i]) == "-link2") {
      if (i + 1 < argc) {
        RAIINet::linkOrderSetup(link2Order, argv[i + 1]);
      }
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
  RAIINet::linkSetup(PlayerId::P1, link1Order);
  RAIINet::linkSetup(PlayerId::P2, link2Order);
  RAIINet::abilitySetup(PlayerId::P1, abilityOrder1);
  RAIINet::abilitySetup(PlayerId::P2, abilityOrder2);
  board_ = std::make_shared<ServerPort>(board_, players[PlayerId::P1], 0, 3);
  board_ = std::make_shared<ServerPort>(board_, players[PlayerId::P1], 0, 4);
  board_ = std::make_shared<ServerPort>(board_, players[PlayerId::P2], 7, 3);
  board_ = std::make_shared<ServerPort>(board_, players[PlayerId::P2], 7, 4);
}

void RAIINet::linkOrderSetup(std::vector<std::string> &order,
                             const std::string &linkFile) {
  std::ifstream file(linkFile.c_str());
  std::string linkInfo;
  order.clear();
  while (file >> linkInfo) {
    order.emplace_back(linkInfo);
  }
}

void RAIINet::linkSetup(PlayerId pid, const std::vector<std::string> &order) {
  using pii = std::pair<int, int>;
  std::vector<pii> linkPos;
  Player &player = players[pid];
  const std::vector<char> &linkChars = player.getLinkChars();
  if (pid == PlayerId::P1) {
    linkPos = {{0, 0}, {0, 1}, {0, 2}, {1, 3}, {1, 4}, {0, 5}, {0, 6}, {0, 7}};
  } else if (pid == PlayerId::P2) {
    linkPos = {{7, 0}, {7, 1}, {7, 2}, {6, 3}, {6, 4}, {7, 5}, {7, 6}, {7, 7}};
  }

  for (int i = 0; i < order.size(); i++) {
    std::string linkInfo = order[i];
    int strength = linkInfo[1] - '0';
    board_ = links[linkChars[i]] = std::make_shared<Link>(
        board_, player, linkPos[i].first, linkPos[i].second, strength,
        linkInfo[0], linkChars[i]);
  }
}

void RAIINet::abilitySetup(PlayerId pid, const std::string &order) {
  auto &player = players[pid];

  for (const auto c : order) {
    player.addAbility(c);
  }
}

void RAIINet::endTurn() {
  int next = static_cast<int>(turn);
  next = (next + 1) % numPlayers;
  turn = static_cast<PlayerId>(next);
  abilityUsed = false;
  displayBoard();

  // Check for winner
  auto &p1 = players[PlayerId::P1];
  auto &p2 = players[PlayerId::P2];
  if (p1.getNumDataDownloaded() == 4 || p2.getNumVirusDownloaded() == 4) {
    std::cout << "Player 1 has won!\n";
    endGame();
  } else if (p1.getNumVirusDownloaded() == 4 ||
             p2.getNumDataDownloaded() == 4) {
    std::cout << "Player 2 has won!\n";
    endGame();
  }
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
  if (links[linkChar]->moveLink(dir, board_, nrows, ncols)) {
    endTurn();
  }
}

bool RAIINet::parseAbilityInput(
    std::shared_ptr<AbilityParams> &abilityParams,
    const std::vector<std::string> &params,
    const std::vector<std::unique_ptr<Ability>> &abilities, const int N) {
  if (dynamic_cast<LinkBoostAbility *>(abilities[N].get())) {
    if (params.size() != 1) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<LinkBoostAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<FirewallAbility *>(abilities[N].get())) {
    if (params.size() != 2) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    try {
      int row = stoi(params[0]), col = stoi(params[1]);

      if (row < 0 || row >= nrows || col < 0 || col >= ncols) {
        std::cout << "Error. Coordinates out of bounds.\n";
        return false;
      }
      abilityParams = std::make_shared<FirewallAbilityParams>(row, col, board_,
                                                              players[turn]);
    } catch (std::exception &err) {
      std::cout << "Error. Invalid number.\n";
    }
  } else if (dynamic_cast<DownloadAbility *>(abilities[N].get())) {
    if (params.size() != 1) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<DownloadAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<PolarizeAbility *>(abilities[N].get())) {
    if (params.size() != 1) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<PolarizeAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<ScanAbility *>(abilities[N].get())) {
    if (params.size() != 1) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<ScanAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<SwapAbility *>(abilities[N].get())) {
    if (params.size() != 2) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar1 = params[0][0], linkChar2 = params[1][0];
    if (links.find(linkChar1) == links.end() ||
        links.find(linkChar2) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams =
        std::make_shared<SwapAbilityParams>(links[linkChar1], links[linkChar2]);
  } else if (dynamic_cast<LinkHideAbility *>(abilities[N].get())) {
    if (params.size() != 1) {
      std::cout << "Error. Invalid input.\n";
      return false;
    }
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<LinkHideAbilityParams>(links[linkChar]);
  } else if (dynamic_cast<LinkCleanseAbility *>(abilities[N].get())) {
    char linkChar = params[0][0];
    if (links.find(linkChar) == links.end()) {
      std::cout << "Error. Link not found.\n";
      return false;
    }
    abilityParams = std::make_shared<LinkCleanseAbilityParams>(links[linkChar]);
  }
  return true;
}

void RAIINet::useAbility(int N, const std::vector<std::string> &params) {
  auto &player = players[turn];
  auto &abilities = player.getAbilities();
  if (N < 1 || N > 6) {
    std::cout << "Error. Invalid input.\n";
    return;
  }
  N--;

  if (abilityUsed) {
    std::cout << "Error. Already used ability this turn.\n";
    return;
  }
  if (abilities[N]->isUsed()) {
    std::cout << "Error. Ability already used.\n";
    return;
  }

  std::shared_ptr<AbilityParams> abilityParams;
  if (!parseAbilityInput(abilityParams, params, abilities, N)) {
    return;
  }

  if (abilities[N]->use(abilityParams)) {
    abilities[N]->setUsed();
    player.useAbility();
    abilityUsed = true;
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
