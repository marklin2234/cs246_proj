#include "subject.hpp"
#include "observer.hpp"

#include <vector>

void Subject::attach(std::unique_ptr<Observer> o) {
  observers.emplace_back(std::move(o));
}

void Subject::detach(std::unique_ptr<Observer> o) { std::erase(observers, o); }

void Subject::notifyObservers() const {
  for (const auto &o : observers) {
    o->notify();
  }
}
