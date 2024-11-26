#pragma once

#include "player.hpp"
#include "serverPort.hpp"
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
  bool linkBattle(std::shared_ptr<Link> l1, std::shared_ptr<Link> l2);
  bool serverDownload(std::shared_ptr<Link> link,
                      std::shared_ptr<ServerPort> server);
  void linkSetup(Player::PlayerId player, const std::string &linkFile);
  void printPlayerInfo(Player::PlayerId player) const;

public:
  explicit RAIINet(std::shared_ptr<Board> board);
  void displayBoard() const;
  void setup(int argc, char **argv);
  void endGame();
  void moveLink(char linkChar, char dir);
};
