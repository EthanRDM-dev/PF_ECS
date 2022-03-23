#pragma once

// #include "ECS.h"
#include "Vec2.h"
#include "RigidBody2.h"

//Oriented Bounding Box
struct Box2 {
    Box2() : size(Vec2{}), halfSize(Vec2{}) {}
    //WARNING: min = top left, max = bottom right, dans le cours il utilise bottom left et top right
    Box2(Vec2 min, Vec2 max) {
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

    Vec2 getCenter() const {
        return rb->position;
    }

    float getRotation() const {
        return rb->rotation;
    }

    //retourne les points de chaque coin de la Box
    Vec2* getVertices() {
        Vec2 min = getMin(), max = getMax();
        Vec2 vertices[] = {
            Vec2{min.x, min.y}, Vec2{min.x, max.y},
            Vec2{max.x, min.y}, Vec2{max.x, max.y}
        };

        if(rb->rotation != 0.0f) {
            for(Vec2 v : vertices) {
                //TODO: implement me
                //rotates point(vec2) about center(vec2) by rotation(float in degrees)
                rotate(v, rb->rotation, rb->position);
            }
        }

        return vertices;
    }

    Vec2 size;
    Vec2 halfSize;
    RigidBody2* rb = nullptr;
};