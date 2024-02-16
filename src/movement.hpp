#pragma once
#include <gladiator.h>

const float DURATION_LINEAR = 0.0f;
const float DURATION_ROTATION = 0.0f;
const float SPEED_ROTATION = 0.5f;
const float SPEED_LINEAR = 0.0f;

class Movement {

public:
  Movement(Gladiator *gladiator);
  void Go(Position cons, Position pos);
  inline bool go_to(Gladiator *gladiator, const Vector2 &target, bool showLogs);
  void Turn();
  void kwak();

private:
  Gladiator *gladiator;
  float last_update_ms;
  float time_remaining_rotation;
  float time_remaining_linear;
  bool target_reached;
};