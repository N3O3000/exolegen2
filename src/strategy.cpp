#include "strategy.hpp"
#define ROBOT_ID_1 13
#define ROBOT_ID_2 61

Strategy::Strategy(Gladiator *gladiator) { this->gladiator = gladiator; }
data_id = RobotData::Game::getOtherRobotData();

void Strategy::logAllData() {
  this->gladiator->printVersionInfo();
  auto square = this->gladiator->maze->getNearestSquare();
  gladiator->log("square: %d %d\n", square->i, square->j);
  auto data = gladiator->robot->getData();
  gladiator->log("x: %f, y: %f", data.cposition.x, data.cposition.y);
  if (data.id == ROBOT_ID_1 || data.id == ROBOT_ID_2) log("id robot1 %i, id robot2 %i",ROBOT_ID_1,ROBOT_ID_2);
}

