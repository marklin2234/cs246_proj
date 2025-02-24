#include "abilityParams.hpp"

AbilityParams::~AbilityParams() {}

LinkBoostAbilityParams::LinkBoostAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

FirewallAbilityParams::FirewallAbilityParams(int row, int col,
                                             std::shared_ptr<Board> &board,
                                             Player &player)
    : row_{row}, col_{col}, board_{board}, player_{player} {}

DownloadAbilityParams::DownloadAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

PolarizeAbilityParams::PolarizeAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

ScanAbilityParams::ScanAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

SwapAbilityParams::SwapAbilityParams(std::shared_ptr<Link> link1,
                                     std::shared_ptr<Link> link2)
    : link1_{link1}, link2_{link2} {}

LinkHideAbilityParams::LinkHideAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}

LinkCleanseAbilityParams::LinkCleanseAbilityParams(std::shared_ptr<Link> link)
    : link_{link} {}
