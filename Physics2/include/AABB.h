//TODO: réorganiser dépendances -> Ce fichier dans Primitives
#pragma once

#include "Vec2.h"
#include "Engine.h"
#include "RigidBody2.h"

//Axis-Aligned Bounding Box
struct AABB {
    //TODO: à voir pour le RigidBody2
    AABB() : size(Vec2{}), halfSize(Vec2{}), rb(new RigidBody2{}) {}
    //WARNING: min = top left, max = bottom right, dans le cours il utilise bottom left et top right
    AABB(Vec2 min, Vec2 max) {
        size = max - min;
        halfSize = size * 0.5f;
    }

    Vec2 getMin() {
        Vec2 min = rb->position - halfSize;
        return min;
    }
    Vec2 getMax() {
        Vec2 max = rb->position + halfSize;
        return max;
    }

    void setSize(Vec2 s) {
        size = s;
        halfSize = s * 0.5f;
    }

    Vec2 size;
    Vec2 halfSize;
    RigidBody2* rb = nullptr;
};