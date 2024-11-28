#pragma once

#include "RAIINet.hpp"
#include "observer.hpp"
#include "player.hpp"
#include "window.hpp"

class GraphicObserver : public Observer {
private:
  static constexpr int SQUARE_SIZE = 50;
  static constexpr int PLAYER_INFO_SIZE = 50;
  static constexpr int BUFFER_SIZE = 10;
  const RAIINet &game_;
  std::unique_ptr<Xwindow> win;

public:
  GraphicObserver(const RAIINet &game);
  void notify() override;
  void printPlayerInfo(PlayerId pid) const;
  void printGameState() const;
};
