#pragma once

#include "link.hpp"
#include <memory>

class AbilityParams {
public:
  virtual ~AbilityParams();
};

class LinkBoostAbilityParams : public AbilityParams {
public:
  std::shared_ptr<Link> link_;
  LinkBoostAbilityParams(std::shared_ptr<Link> link);
};

class FirewallAbilityParams : public AbilityParams {
public:
  int row_, col_;
  std::shared_ptr<Board> &board_;
  Player &player_;
  FirewallAbilityParams(int row, int col, std::shared_ptr<Board> &board,
                        Player &player);
};
