#pragma once

#include "ECS.h"

struct AI : IComponent<AI> {
    enum AIState {IDLE, ATTACK, FLEEING};

    AI() : IComponent<AI>() {}
    AI(Entity e) : IComponent<AI>(e) {}

    AIState state;
    //TODO: type d'ennemi/d'IA ? State ?
};