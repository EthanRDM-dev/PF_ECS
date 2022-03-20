#pragma once

#include "ECS.h"
#include "Vec2.h"

struct RigidBody2 : IComponent<RigidBody2> {
    RigidBody2() : position(Vec2{}), rotation(0.0f) {}
    RigidBody2(Vec2 pos, float rot) : position(pos), rotation(rot) {}
    //RigidBody2() {}

    //FIXME: DOIT ETRE LE CENTRE
    Vec2 position;
    float rotation;
};