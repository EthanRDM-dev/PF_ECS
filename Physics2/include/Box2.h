//TODO: réorganiser dépendances -> Ce fichier dans Primitives
#pragma once

// #include "ECS.h"
#include "Vec2.h"
#include "RigidBody2.h"
#include "Maths.h"

//TODO: IComponent ? If yes -> query RigidBody2 from id
//Oriented Bounding Box
struct Box2 {
    Box2() : size(Vec2{}), halfSize(Vec2{}) {}
    //FIXME: min = top left, max = bottom right, dans le cours il utilise bottom left et top right
    Box2(Vec2 min, Vec2 max) {
        size = max - min;
        halfSize = size * 0.5f;
    }

    //retourne les points de chaque coin de la Box
    Vec2* getVertices() {
        Vec2 min = getLocalMin(), max = getLocalMax();
        Vec2 vertices[] = {
            Vec2{min.x, min.y}, Vec2{min.x, max.y},
            Vec2{max.x, min.y}, Vec2{max.x, max.y}
        };

        if(rb->rotation != 0.0f) {
            for(Vec2 v : vertices) {
                //rotates point(vec2) about center(vec2) by rotation(float in degrees)
                rotate(v, rb->rotation, rb->position);
            }
        }

        return vertices;
    }

    //TODO: Physics Engine #12 5:40
    Vec2 getLocalMin() {
        Vec2 min = rb->position - halfSize;
        return min;
    }
    Vec2 getLocalMax() {
        Vec2 max = rb->position + halfSize;
        return max;
    }

    Vec2 getCenter() const {
        return rb->position;
    }

    float getRotation() const {
        return rb->rotation;
    }

    void setSize(Vec2 s) {
        size = s;
        halfSize = s * 0.5f;
    }

    Vec2 size;
    Vec2 halfSize;
    RigidBody2* rb = nullptr;
};