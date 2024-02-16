#include "gladiator.h"
#include "strategy.hpp"
#include "movement.hpp"

Gladiator *gladiator;
Strategy *strategy;
Movement *movement;

void reset();

void setup() {
  gladiator = new Gladiator();
  strategy = new Strategy(gladiator);
  movement = new Movement(gladiator);

  gladiator->game->onReset(&reset);
  Position initialPosition = {32, 32, 0};
  gladiator->game->enableFreeMode(RemoteMode::OFF, initialPosition);
}

void reset() { gladiator->log("Call of reset function"); }

void loop() {
  if (gladiator->game->isStarted()) {
    gladiator->log("Gladiator - Game Started");
    strategy->logAllData();

  } else {
    gladiator->log("Gladiator - Game not Startd yet");
  }
  delay(300);
}