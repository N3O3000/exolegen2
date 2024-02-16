#pragma once
#include "gladiator.h"

class Strategy {
  Gladiator *gladiator;

public:
  Strategy(Gladiator *gladiator);
  void logAllData();

private:
};