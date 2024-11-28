#pragma once

#include "player.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>

class Board;

class RAIINet {
private:
  int nrows = 8, ncols = 8, numPlayers = 2;
  PlayerId turn = PlayerId::P1;
  std::shared_ptr<Board> board_;
  std::ostream &out = std::cout;

  std::unordered_map<char, std::shared_ptr<Link>> links;
  std::unordered_map<PlayerId, Player, PlayerHash> players;

  std::pair<int, int> directionToVector(char dir) const;
  void linkOrderSetup(std::vector<std::string> &order,
                      const std::string &linkFile);
  void linkSetup(PlayerId player, const std::vector<std::string> &order);
  void abilitySetup(PlayerId player, const std::string &order = "LFDSP");
  void printPlayerInfo(PlayerId player) const;
  void endTurn();

public:
  explicit RAIINet(std::shared_ptr<Board> board);
  void displayBoard() const;
  void setup(int argc, char **argv);
  void endGame();
  void moveLink(char linkChar, char dir);
  void useAbility(int N, const std::vector<std::string> &params);
  void displayAbilities() const;
};
