#include "RAIINet.hpp"
#include "blank.hpp"
#include "board.hpp"
#include <memory>

int main(int argc, char **argv) {
  std::shared_ptr<Board> board = std::make_shared<Blank>();
  RAIINet game{board};

  game.setup(argc, argv);

  std::string command;

  while (std::cin >> command) {
    if (command == "move") {
      char link, direction;
      std::cin >> link >> direction;

      game.moveLink(link, direction);
    } else if (command == "abilities") {

    } else if (command == "ability") {

    } else if (command == "board") {
      game.displayBoard();
    } else if (command == "sequence") {

    } else if (command == "quit") {
    }
  }
}
