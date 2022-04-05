/**
 * @file PhysicSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Resolve forces and update the velocity of the Entities (the position's update is made in CollisionSystem)
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Manager.h"
#include "Transform.h"
#include "RigidBody.h"

struct PhysicSystem : public ISystem {
    PhysicSystem() {
        systemSignature[getComponentTypeID<Transform>()] = true;
        systemSignature[getComponentTypeID<RigidBody>()] = true;
    }

    bool isUpdatable(Signature entitySignature) override {
        bool updatable = true;
        for(int i = 0 ; i < systemSignature.size() ; i++) {
            if(systemSignature[i]) {
                updatable &= systemSignature[i] && entitySignature[i];
            }
        }
        return updatable;
    }

    void update(float dt) override {
        SignatureArray& signArr = Manager::get().getSignatureArray();
        for(Entity i = 0 ; i < MAX_ENTITIES ; i++) {
            if(isUpdatable(signArr[i])) {
                Transform& t = Manager::get().getComponent<Transform>(i);
                RigidBody& r = Manager::get().getComponent<RigidBody>(i);
                
                if(r.type == BodyType::DYNAMIC) {
                    r.acceleration.x = (r.force.x - r.drag.x) / r.mass;
                    r.acceleration.y = (GRAVITY.y * r.gravScale) + (r.force.y / r.mass);

                    r.velocity = r.acceleration * dt;
                }
            }
        }
    }

    Signature systemSignature;
};