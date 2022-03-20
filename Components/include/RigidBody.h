#pragma once

#include "ECS.h"
#include "Vec2.h"

constexpr float GRAVITY = 9.8f;

struct RigidBody : public IComponent<RigidBody> {
    RigidBody() {}
    RigidBody(Entity e, float _mass = 0.0f, float _gravScale = 0.0f, Vec2 _force = ZEROS, Vec2 _drag = ZEROS, Vec2 _velocity = ZEROS) 
        : IComponent<RigidBody>(e), mass(_mass), gravScale(_gravScale), force(_force), drag(_drag), velocity(_velocity) {}
    ~RigidBody() = default;

    float mass;
    float gravScale;
    Vec2 force;
    Vec2 drag;
    Vec2 velocity;
};
