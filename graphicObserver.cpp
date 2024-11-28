#include "graphicObserver.hpp"
#include "link.hpp"
#include "window.hpp"
#include <sstream>

GraphicObserver::GraphicObserver(const RAIINet &game)
    : game_{game},
      win{std::make_unique<Xwindow>(
          game.ncols * SQUARE_SIZE,
          game.nrows * SQUARE_SIZE + 2 * PLAYER_INFO_SIZE + 2 * BUFFER_SIZE)} {}

void GraphicObserver::notify() {
  int nrows = game_.nrows, ncols = game_.ncols;
  win->fillRectangle(0, 0, ncols * SQUARE_SIZE,
                     nrows * SQUARE_SIZE + 2 * PLAYER_INFO_SIZE +
                         2 * BUFFER_SIZE,
                     Xwindow::White);
  printPlayerInfo(PlayerId::P1);
  printGameState();
  printPlayerInfo(PlayerId::P2);
}

void GraphicObserver::printPlayerInfo(PlayerId pid) const {
  const auto &links = game_.links;
  const auto turn = game_.turn;
  const auto &player = game_.players.at(pid);
  const auto &seenLinks = game_.players.at(turn).getSeen();
  std::stringstream ss;
  int y = (pid == PlayerId::P1 ? 10 : win->getHeight() - PLAYER_INFO_SIZE),
      x = 10;
  ss << "Player " << static_cast<int>(pid) + 1 << ":";
  win->drawString(x, y, ss.str());
  ss.str(std::string());
  y += 10;
  ss << "Downloaded: " << std::to_string(player.getNumDataDownloaded()) << "D, "
     << std::to_string(player.getNumVirusDownloaded()) << "V";
  win->drawString(x, y, ss.str());
  ss.str(std::string());
  y += 10;
  ss << "Abilities: " << player.getNumAbilities();
  win->drawString(x, y, ss.str());
  ss.str(std::string());
  y += 10;
  int i = 0;
  for (const auto c : player.getLinkChars()) {
    ss << c << ": ";
    if (player.getPlayerId() == turn ||
        std::find(seenLinks.begin(), seenLinks.end(), c) != seenLinks.end()) {
      ss << links.at(c)->typeChar() << links.at(c)->getStrength();
    } else {
      ss << "?";
    }
    if (i == 3) {
      win->drawString(x, y, ss.str());
      ss.str(std::string());
      y += 10;
    }
    i++;
  }
  win->drawString(x, y, ss.str());
  ss.str(std::string());
  y += 10;

  win->drawString(x, y, ss.str());
}

void GraphicObserver::printGameState() const {
  int nrows = game_.nrows, ncols = game_.ncols;
  const auto &links = game_.links;
  const auto turn = game_.turn;
  const auto &seen = game_.players.at(turn).getSeen();
  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      auto state = game_.getState(i, j);
      int colour = Xwindow::White;
      if (links.find(state) != links.end()) {
        if (links.at(state)->getPlayer().getPlayerId() != turn &&
            seen.find(state) == seen.end()) {
          colour = Xwindow::Black;
        } else if (links.at(state)->getLinkType() == LinkType::Virus) {
          colour = Xwindow::Red;
        } else {
          colour = Xwindow::Green;
        }
      } else if (state == 'W' || state == 'M') {
        colour = Xwindow::Blue;
      } else if (state == 'S') {
        colour = Xwindow::Yellow;
      }
      win->fillRectangle(j * SQUARE_SIZE,
                         i * SQUARE_SIZE + PLAYER_INFO_SIZE + BUFFER_SIZE,
                         SQUARE_SIZE, SQUARE_SIZE, colour);
    }
  }
}
