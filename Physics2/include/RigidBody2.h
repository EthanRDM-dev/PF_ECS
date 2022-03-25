//TODO: réorganiser dépendances -> Ce fichier dans RigidBody
#pragma once

#include "ECS.h"
#include "Vec2.h"

struct RigidBody2 : IComponent<RigidBody2> {
    RigidBody2() : position(Vec2{}), rotation(0.0f), linVelocity(Vec2{}),
        angVelocity(0.0f), linDamping(0.0f), angDamping(0.0f), fixedRotation(false) {}
    RigidBody2(Vec2 pos, float rot) : position(pos), rotation(rot) {}

    void setTransform(Vec2 pos) {
        position = pos;
    }

    void setTransform(Vec2 pos, float rot) {
        position = pos;
        rotation = rot;
    }

    //REMINDER: DOIT ETRE LE CENTRE
    Vec2 position;
    float rotation;

    Vec2 linVelocity;
    float angVelocity;
    float linDamping; //amortissement linéaire, les frottements en gros
    float angDamping; //amortissement angulaire, les frottements en gros

    bool fixedRotation;
};