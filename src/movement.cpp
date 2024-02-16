#include "movement.hpp"
#include "utils.hpp"

Movement::Movement(Gladiator *gladiator) {
  this->gladiator = gladiator;
  last_update_ms = 0.0f;
  time_remaining_linear = 0.0f;
  time_remaining_linear = 0.0f;
  target_reached = true;
};

double reductionAngle(double x) {
  x = fmod(x + PI, 2 * PI);
  if (x < 0)
    x += 2 * PI;
  return x - PI;
}

void Movement::Go(Position cons, Position pos) {
  target_reached = false;
  float time_elapsed = 0.0f;
  float last_ms = 0.0f;
  while (!target_reached) {
    this->gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.5);
    this->gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.5);
  }
  float kw = 1.2;
  float kv = 1.f;
  float wlimit = 3.f;
  float vlimit = 0.6;
  float erreurPos = 0.07;

  double consvl, consvr;
  double dx = cons.x - pos.x;
  double dy = cons.y - pos.y;
  double d = sqrt(dx * dx + dy * dy);

  if (d > erreurPos) {
    double rho = atan2(dy, dx);
    double consw = kw * reductionAngle(rho - pos.a);

    double consv = kv * d * cos(reductionAngle(rho - pos.a));
    consw = abs(consw) > wlimit ? (consw > 0 ? 1 : -1) * wlimit : consw;
    consv = abs(consv) > vlimit ? (consv > 0 ? 1 : -1) * vlimit : consv;

    consvl = consv - gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
    consvr = consv + gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
  } else {
    consvr = 0;
    consvl = 0;
  }
  gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr,
                                    false); // GFA 3.2.1
  gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl,
                                    false); // GFA 3.2.1
}

inline float moduloPi(float a) // return angle in [-pi; pi]
{
  return (a < 0.0) ? (std::fmod(a - M_PI, 2 * M_PI) + M_PI)
                   : (std::fmod(a + M_PI, 2 * M_PI) - M_PI);
}

inline bool go_to(Gladiator *gladiator, const Vector2 &target, bool showLogs) {
  constexpr float ANGLE_REACHED_THRESHOLD = 0.1;
  constexpr float POS_REACHED_THRESHOLD = 0.05;

  auto posRaw = gladiator->robot->getData().position;
  Vector2 pos{posRaw.x, posRaw.y};

  Vector2 posError = target - pos;

  float targetAngle = posError.angle();
  float angleError = moduloPi(targetAngle - posRaw.a);

  bool targetReached = false;
  float leftCommand = 0.f;
  float rightCommand = 0.f;

  if (posError.norm2() < POS_REACHED_THRESHOLD) //
  {
    targetReached = true;
  } else if (std::abs(angleError) > ANGLE_REACHED_THRESHOLD) {
    float factor = 0.2;
    if (angleError < 0)
      factor = -factor;
    rightCommand = factor;
    leftCommand = -factor;
  } else {
    float factor = 0.5;
    rightCommand = factor; //+angleError*0.1  => terme optionel, "pseudo
                           // correction angulaire";
    leftCommand = factor;  //-angleError*0.1   => terme optionel, "pseudo
                           // correction angulaire";
  }

  gladiator->control->setWheelSpeed(WheelAxis::LEFT, leftCommand);
  gladiator->control->setWheelSpeed(WheelAxis::RIGHT, rightCommand);

  if (showLogs || targetReached) {
    gladiator->log("ta %f, ca %f, ea %f, tx %f cx %f ex %f ty %f cy %f ey %f",
                   targetAngle, posRaw.a, angleError, target.x(), pos.x(),
                   posError.x(), target.y(), pos.y(), posError.y());
  }

  return targetReached;
}