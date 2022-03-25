//TODO: réorganiser dépendances -> Ce fichier dans Primitives
#pragma once

#include "Vec2.h"
#include "Engine.h"
#include "RigidBody2.h"

struct Circle {
    Circle() : radius(1.0f) {}
    Circle(float r) : radius(r) {}

    Vec2 getCenter() {
        return rb->position;
    }

    float radius;
    RigidBody2* rb = nullptr;
};