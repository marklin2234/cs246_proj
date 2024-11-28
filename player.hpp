#pragma once

#include "ability.hpp"
#include <unordered_map>
#include <vector>

class Link;

enum class PlayerId { P1, P2 };
struct PlayerHash {
  template <typename T> std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

class Player {
private:
  int numDataDownloaded = 0, numVirusDownloaded = 0, numUnusedAbilities = 5;
  PlayerId id_;
  std::vector<char> linkChars;
  std::vector<std::unique_ptr<Ability>> abilities;
  std::unordered_map<char, std::shared_ptr<Link>> seen;

public:
  Player() = default;
  Player(PlayerId id);
  Player(const Player &player) = delete;
  Player(Player &&player);
  Player &operator=(const Player &player) = delete;
  Player &operator=(Player &&player);

  void addDownload(std::shared_ptr<Link> link);
  int getNumDataDownloaded() const;
  int getNumVirusDownloaded() const;
  void addAbility(char ability);
  PlayerId getPlayerId() const;
  const std::vector<char> &getLinkChars() const;
  const std::vector<std::unique_ptr<Ability>> &getAbilities() const;
  int getNumAbilities() const;
  void useAbility();
  void addSeen(std::shared_ptr<Link> link);
  const std::unordered_map<char, std::shared_ptr<Link>> getSeen() const;
};
