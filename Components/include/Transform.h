/**
 * @file Transform.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Transform component, contains the position (and the "safe" position, to resolve collision), scale, and rotation of an entity
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Vec2.h"

struct Transform : public IComponent<Transform> {
    Transform() {}
    Transform(Entity e, Vec2 pos = ZEROS, Vec2 scl = ONES, float rot = 0)
        : IComponent<Transform>(e), position(pos), scale(scl), rotation(rot) {}
    ~Transform() = default;

    Vec2 lastSafePos;
    Vec2 position;
    Vec2 scale;
    float rotation;
};