#pragma once

#include "ECS.h"
#include "Manager.h"
#include "Transform.h"
#include "RigidBody.h"

struct PhysicSystem : public ISystem {
    PhysicSystem() {
        systemSignature[getComponentTypeID<Transform>()] = true;
        systemSignature[getComponentTypeID<RigidBody>()] = true;
        //FIXME: autre ?
    }

    //TODO: même principe  pour chaque System
    bool isUpdatable(Signature entitySignature) override {
        bool updatable = true;
        for(int i = 0 ; i < systemSignature.size() ; i++) {
            if(systemSignature[i]) {
                updatable &= systemSignature[i] && entitySignature[i];
            }
        }
        return updatable;
    }

    void update() override {
        SignatureArray& signArr = Manager::get().getSignatureArray();
        for(Entity i = 0 ; i < MAX_ENTITIES ; i++) {
            if(isUpdatable(signArr[i])) {
                Transform& t = Manager::get().getComponent<Transform>(i);
                RigidBody& r = Manager::get().getComponent<RigidBody>(i);

                r.velocity.x = r.force.x - r.drag.x;
                r.velocity.y = r.force.y + r.drag.y + r.gravScale * GRAVITY * r.mass;

                t.position.x += r.velocity.x;
                t.position.y += r.velocity.y;
            }
        }
    }

    Signature systemSignature;
};