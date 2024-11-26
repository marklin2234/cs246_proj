#pragma once

#include "player.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>

class Board;

class RAIINet {
private:
  int nrows = 8, ncols = 8;
  std::shared_ptr<Board> board_;
  std::ostream &out = std::cout;

  std::unordered_map<char, std::shared_ptr<Link>> links;
  std::unordered_map<Player::PlayerId, std::shared_ptr<Player>,
                     Player::PlayerHash>
      players;

  std::pair<int, int> directionToVector(char dir) const;
  void linkSetup(Player::PlayerId player, const std::string &linkFile);
  void printPlayerInfo(Player::PlayerId player) const;

public:
  explicit RAIINet(std::shared_ptr<Board> board);
  void displayBoard() const;
  void setup(int argc, char **argv);
  void endGame();
  void moveLink(char linkChar, char dir);
};
