#pragma once
#include <gladiator.h>

const float MAX_AIM_DISTANCE = 5;
const float ROCKET_SPEED = 0.6;


class rocket {

public:
    Position GetNearestEnemyBotPos(Gladiator *gladiator)
    bool isInAimRange(Gladiator *gladiator, Position object)
    Gladiator *gladiator;
    bool target_reached;
    bool isRocket;
private:

};