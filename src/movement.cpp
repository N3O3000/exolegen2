#include "movement.hpp"
#include "Arduino.h"

double reductionAngle(double x) {
  x = fmod(x + PI, 2 * PI);
  if (x < 0)
    x += 2 * PI;
  return x - PI;
}

Movement::Movement(Gladiator *gladiator) {
  this->gladiator = gladiator;
  currentPosition = gladiator->robot->getData().position;
};
void Movement::setPosition(Position pos) { this->currentPosition = pos; }

void Movement::GoTo(Position cons) {
  double consvl, consvr;
  double dx = cons.x - currentPosition.x;
  double dy = cons.y - currentPosition.y;
  double d = sqrt(dx * dx + dy * dy);

  if (d > erreurPos) {
    double rho = atan2(dy, dx);
    double consw = kw * reductionAngle(rho - currentPosition.a);
    double consv = kv * d * cos(reductionAngle(rho - currentPosition.a));
    consw = abs(consw) > wlimit ? (consw > 0 ? 1 : -1) * wlimit : consw;
    consv = abs(consv) > vlimit ? (consv > 0 ? 1 : -1) * vlimit : consv;
    consvl = consv - gladiator->robot->getRobotRadius() * consw;
    consvr = consv + gladiator->robot->getRobotRadius() * consw;
  } else {
    consvr = 0;
    consvl = 0;
  }
  gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr, false);
  gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl, false);
}