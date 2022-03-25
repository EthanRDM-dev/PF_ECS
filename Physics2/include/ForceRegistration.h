#pragma once

#include "RigidBody2.h"
#include "IForceGenerator.h"

struct ForceRegistration {
    ForceRegistration(RigidBody2 r, IForceGenerator f) : rb(r), fg(f) {}

    RigidBody2 rb;
    IForceGenerator fg;
};