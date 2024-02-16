#include "strategy.hpp"

Strategy::Strategy(Gladiator *gladiator) { this->gladiator = gladiator; }

void Strategy::logAllData() {
  this->gladiator->printVersionInfo();
  auto square = this->gladiator->maze->getNearestSquare();
  gladiator->log("square: %d %d\n", square->i, square->j);
  auto data = gladiator->robot->getData();
  gladiator->log("x: %f, y: %f", data.cposition.x, data.cposition.y);
  
}

