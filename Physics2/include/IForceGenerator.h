#pragma once

#include "RigidBody2.h"

struct IForceGenerator {
    virtual void updateForce(RigidBody2& rb, float dt);

    //TODO: ajout d'un id pour les forces ? -> comme ça on compare les id de f et de this
    bool operator==(const IForceGenerator& f) {
        return true;
    }
};