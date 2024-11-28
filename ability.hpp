#pragma once

#include <memory>

class AbilityParams;
class Player;

class Ability {
protected:
  Player &player_;
  bool used_;

public:
  Ability(Player &player);
  virtual ~Ability() = default;

  virtual void use(const std::shared_ptr<AbilityParams> params) = 0;
  virtual char displayChar() const = 0;
  Player &getPlayer() const;
  bool isUsed() const;
  void setUsed();
};
