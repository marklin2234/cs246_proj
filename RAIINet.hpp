#pragma once

#include "player.hpp"
#include "subject.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>

class Board;

class RAIINet : public Subject {
private:
  int nrows = 8, ncols = 8, numPlayers = 2;
  PlayerId turn = PlayerId::P1;
  bool abilityUsed = false;
  bool isGameOver = false;
  std::shared_ptr<Board> board_;
  std::ostream &out = std::cout;

  std::unordered_map<char, std::shared_ptr<Link>> links;
  std::unordered_map<PlayerId, Player, PlayerHash> players;

  std::pair<int, int> directionToVector(char dir) const;
  void linkOrderSetup(std::vector<std::string> &order,
                      const std::string &linkFile);
  void linkSetup(PlayerId player, const std::vector<std::string> &order);
  void abilitySetup(PlayerId player, const std::string &order = "LFDSP");
  bool parseAbilityInput(std::shared_ptr<AbilityParams> &abilityParams,
                         const std::vector<std::string> &params,
                         const std::vector<std::unique_ptr<Ability>> &abilities,
                         const int N);
  void endTurn();
  void endGame();

public:
  explicit RAIINet(std::shared_ptr<Board> board);
  void displayBoard() const;
  char getState(int row, int col) const override;
  void setup(int argc, char **argv);
  bool getIsGameOver() const;
  void moveLink(char linkChar, char dir);
  void useAbility(int N, const std::vector<std::string> &params);
  void displayAbilities() const;

  friend class TextObserver;
  friend class GraphicObserver;
};
