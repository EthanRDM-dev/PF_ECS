/**
 * @file RigidBody.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief RigidBody component, used to resolve physic calculations
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Vec2.h"

#define GRAVITY (Vec2) {0, 9.8f}

//Direction UP (not just UP, defined for Vec2)
constexpr int D_UP = -1;
//Direction DOWN (not just DOWN, defined for Vec2)
constexpr int D_DOWN = 1;
//Direction RIGHT (not just RIGHT, defined for Vec2)
constexpr int D_RIGHT = 1;
//Direction LEFT (not just LEFT, defined for Vec2)
constexpr int D_LEFT = -1;

// jump defines
constexpr float JUMP_TIME = 15.0f;
constexpr float JUMP_FORCE = 20.0f;

/**
 * @brief Type of the Rigidbody, STATIC means absolutely no movement, DYNAMIC means all forces,
 *          KINEMATIC means no forces but movement (potentially scripted)
 *  
 */
typedef enum _BodyType {
    STATIC, //no movements
    DYNAMIC, //movements and forces
    KINEMATIC //movements but no forces
} BodyType;

struct RigidBody : public IComponent<RigidBody> {
    RigidBody() : IComponent<RigidBody>() {}
    RigidBody(Entity e, BodyType _type = BodyType::DYNAMIC, float _mass = 1.0f, float _gravScale = 1.0f, Vec2 _force = ZEROS, Vec2 _drag = ZEROS, Vec2 _velocity = ZEROS, Vec2 _acceleration = ZEROS) 
        : IComponent<RigidBody>(e), type(_type), mass(_mass), gravScale(_gravScale), force(_force), drag(_drag), velocity(_velocity), acceleration(_acceleration), onGround(false), jumping(false), jumpTime(JUMP_TIME), jumpForce(JUMP_FORCE) {}
    ~RigidBody() = default;

    void clearForce() {
        force = Vec2{};
    }

    BodyType type;

    bool onGround;
    bool jumping;

    float jumpTime;
    float jumpForce;

    float mass;
    float gravScale;

    Vec2 force;
    Vec2 drag;
    Vec2 velocity;
    Vec2 acceleration;
};