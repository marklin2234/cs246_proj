#include "polarizeAbility.hpp"
#include "abilityParams.hpp"
#include "link.hpp"

PolarizeAbility::PolarizeAbility(Player &player) : Ability{player} {}

bool PolarizeAbility::use(const std::shared_ptr<AbilityParams> params) {
  auto p = static_pointer_cast<PolarizeAbilityParams>(params);

  const auto &[link] = *p;
  if (link->getLinkType() == LinkType::Virus) {
    link->setLinkType(LinkType::Data);
  } else if (link->getLinkType() == LinkType::Data) {
    link->setLinkType(LinkType::Virus);
  }
  return true;
}

char PolarizeAbility::displayChar() const { return 'P'; }
