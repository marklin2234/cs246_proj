#pragma once

#include <memory>

class AbilityParams;
enum class PlayerId;

class Ability {
protected:
  PlayerId player_;
  bool used_;

public:
  Ability(PlayerId player);
  virtual ~Ability() = default;

  virtual void use(const std::shared_ptr<AbilityParams> params) = 0;
  virtual char displayChar() const = 0;
  PlayerId getPlayerId() const;
  bool isUsed() const;
  void setUsed();
};
