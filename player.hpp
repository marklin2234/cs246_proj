#pragma once

#include <vector>

class Link;

class Player {
public:
  enum class PlayerId { P1, P2 };
  struct PlayerHash {
    template <typename T> std::size_t operator()(T t) const {
      return static_cast<std::size_t>(t);
    }
  };

private:
  PlayerId id_;
  std::vector<std::shared_ptr<Link>> downloaded;
  std::vector<char> linkChars;
  // std::vector<Ability> abilities;
public:
  Player(PlayerId id);
  void addDownload(std::shared_ptr<Link> link);
  std::vector<std::shared_ptr<Link>> getDownloaded() const;
  PlayerId getPlayerId() const;
  std::vector<char> getLinkChars() const;
};
