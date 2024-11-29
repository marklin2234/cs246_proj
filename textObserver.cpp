#include "textObserver.hpp"
#include "link.hpp"

TextObserver::TextObserver(const RAIINet &game) : game_{game} {}

void TextObserver::notify() {
  int i, j;
  int nrows = game_.nrows, ncols = game_.ncols;
  printPlayerInfo(PlayerId::P1);
  for (i = 0; i < ncols; i++) {
    out << "=";
  }
  out << "\n";
  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      out << game_.getState(i, j);
    }
    out << "\n";
  }
  for (i = 0; i < ncols; i++) {
    out << "=";
  }
  out << "\n";
  printPlayerInfo(PlayerId::P2);
}

void TextObserver::printPlayerInfo(PlayerId pid) const {
  const auto &links = game_.links;
  const auto turn = game_.turn;
  const auto &player = game_.players.at(pid);
  const auto &seenLinks = game_.players.at(turn).getSeen();
  out << "Player " << static_cast<int>(pid) + 1 << ":\n";
  out << "Downloaded: " << std::to_string(player.getNumDataDownloaded())
      << "D, " << std::to_string(player.getNumVirusDownloaded()) << "V";
  out << "\n";
  out << "Abilities: " << player.getNumAbilities();
  out << "\n";
  int i = 0;
  for (const auto c : player.getLinkChars()) {
    out << c << ": ";
    if (player.getPlayerId() == turn || seenLinks.find(c) != seenLinks.end()) {
      out << links.at(c)->typeChar() << links.at(c)->getStrength();
    } else {
      out << "?";
    }
    out << ((i == 3) ? "\n" : " ");
    i++;
  }
  out << "\n";
}
