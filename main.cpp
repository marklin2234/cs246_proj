#include "RAIINet.hpp"
#include "blank.hpp"
#include "board.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

void run(std::istream &in, RAIINet &game);

int main(int argc, char **argv) {
  std::shared_ptr<Board> board = std::make_shared<Blank>();
  RAIINet game{board};

  game.setup(argc, argv);
  run(std::cin, game);
}

void run(std::istream &in, RAIINet &game) {
  std::string command;
  while (in >> command) {
    if (command == "move") {
      char link, direction;
      in >> link >> direction;

      game.moveLink(link, direction);
    } else if (command == "abilities") {
      game.displayAbilities();
    } else if (command == "ability") {
      int N;
      std::vector<std::string> params;
      in >> N;
      std::string param;
      std::getline(in, param);
      std::stringstream ss(param);
      while (ss >> param) {
        params.emplace_back(param);
      }
      game.useAbility(N, params);
    } else if (command == "board") {
      game.displayBoard();
    } else if (command == "sequence") {
      std::string fileName;
      in >> fileName;

      std::ifstream file(fileName.c_str());
      run(file, game);
    } else if (command == "quit") {
    }
  }
}
