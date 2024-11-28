#pragma once

#include "RAIINet.hpp"
#include "observer.hpp"
#include "player.hpp"
#include <iostream>

class TextObserver : public Observer {
private:
  const RAIINet &game_;
  std::ostream &out = std::cout;

public:
  TextObserver(const RAIINet &game);
  void notify() override;
  void printPlayerInfo(PlayerId pid) const;
};
