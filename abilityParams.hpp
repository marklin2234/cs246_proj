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

class DownloadAbilityParams : public AbilityParams {
public:
  std::shared_ptr<Link> link_;
  DownloadAbilityParams(std::shared_ptr<Link> link);
};

class PolarizeAbilityParams : public AbilityParams {
public:
  std::shared_ptr<Link> link_;
  PolarizeAbilityParams(std::shared_ptr<Link> link);
};

class ScanAbilityParams : public AbilityParams {
public:
  std::shared_ptr<Link> link_;
  ScanAbilityParams(std::shared_ptr<Link> link);
};

class SwapAbilityParams : public AbilityParams {
public:
  std::shared_ptr<Link> link1_, link2_;
  SwapAbilityParams(std::shared_ptr<Link> link1, std::shared_ptr<Link> link2);
};
