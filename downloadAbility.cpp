#include "downloadAbility.hpp"
#include "ability.hpp"
#include "abilityParams.hpp"
#include <iostream>

DownloadAbility::DownloadAbility(Player &player) : Ability{player} {}

void DownloadAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<DownloadAbilityParams>(params);

  const auto &[link] = *p;

  if (getPlayer().getPlayerId() == link->getPlayer().getPlayerId()) {
    std::cout << "Error. Cannot download own link.\n";
    return;
  }
  getPlayer().addDownload(link);
}

char DownloadAbility::displayChar() const { return 'D'; }
