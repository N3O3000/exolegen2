#pragma once
#include <gladiator.h>
#include <utils.hpp>

class Movement {
public:
  Movement(Gladiator *gladiator);
  void GoTo(Position target);
  void setPosition(Position pos);

private:
  Gladiator *gladiator;
  Position currentPosition;
  float kw = 1.2;
  float kv = 1.f;
  float wlimit = 3.f;
  float vlimit = 0.5;
  float erreurPos = 0.07;
};