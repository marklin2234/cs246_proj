#pragma once

#include "observer.hpp"
#include <memory>
#include <vector>

class Subject {
  std::vector<std::unique_ptr<Observer>> observers;

public:
  void attach(std::unique_ptr<Observer> o);
  void detach(std::unique_ptr<Observer> o);
  void notifyObservers() const;
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};
