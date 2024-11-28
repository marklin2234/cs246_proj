#include "abilityParams.hpp"

AbilityParams::~AbilityParams() {}

LinkBoostAbilityParams::LinkBoostAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

FirewallAbilityParams::FirewallAbilityParams(int row, int col,
                                             std::shared_ptr<Board> &board,
                                             Player &player)
    : row_{row}, col_{col}, board_{board}, player_{player} {}
