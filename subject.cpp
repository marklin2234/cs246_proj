#include "subject.hpp"
#include "observer.hpp"

#include <vector>

void Subject::attach(Observer *o) { observers.push_back(o); }

void Subject::detach(Observer *o) { std::erase(observers, o); }

void Subject::notifyObservers() const {
  for (const auto o : observers) {
    o->notify();
  }
}
